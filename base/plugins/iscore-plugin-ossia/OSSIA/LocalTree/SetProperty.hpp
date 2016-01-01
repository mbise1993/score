#pragma once
#include <OSSIA/LocalTree/BaseCallbackWrapper.hpp>
#include <OSSIA/iscore2OSSIA.hpp>
#include <OSSIA/OSSIA2iscore.hpp>

template<typename T, typename SetFun>
struct SetPropertyWrapper : public BaseCallbackWrapper
{
        SetFun setFun;

        SetPropertyWrapper(
                const std::shared_ptr<OSSIA::Node>& param_node,
                const std::shared_ptr<OSSIA::Address>& param_addr,
                SetFun prop
                ):
            BaseCallbackWrapper{param_node, param_addr},
            setFun{prop}
        {
            callbackIt = addr->addCallback([=] (const OSSIA::Value* v) {
                setFun(Ossia::convert::ToValue(v));
            });

            addr->setValue(new typename Ossia::convert::MatchingType<T>::type);
        }
};

template<typename T, typename Callback>
auto make_setProperty(
        const std::shared_ptr<OSSIA::Node>& node,
        const std::shared_ptr<OSSIA::Address>& addr,
        Callback prop)
{
    return std::make_unique<SetPropertyWrapper<T, Callback>>(node, addr, prop);
}

template<typename T, typename Callback>
auto add_setProperty(OSSIA::Node& n, const std::string& name, Callback cb)
{
    std::shared_ptr<OSSIA::Node> node = *n.emplaceAndNotify(n.children().end(), name);
    auto addr = node->createAddress(Ossia::convert::MatchingType<T>::val);
    addr->setAccessMode(OSSIA::Address::AccessMode::SET);

    return make_setProperty<T>(node, addr, cb);
}
