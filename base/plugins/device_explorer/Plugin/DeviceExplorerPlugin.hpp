#pragma once
#include <QObject>
#include <iscore/plugins/qt_interfaces/PanelFactoryInterface_QtInterface.hpp>
#include <iscore/plugins/qt_interfaces/FactoryFamily_QtInterface.hpp>
#include <iscore/plugins/qt_interfaces/FactoryInterface_QtInterface.hpp>
#include <DeviceExplorer/Protocol/ProtocolList.hpp>
#include <DeviceExplorer/Protocol/DeviceList.hpp>

class SingletonProtocolList
{
    public:
        static ProtocolList& instance();

    private:
        static ProtocolList m_instance;
};

class SingletonDeviceList
{
    public:
        static DeviceList& instance();
        static bool check(const QString& condition)
        {
            // TODO thorought testing required
            if(condition.isEmpty())
            {
                qDebug() << Q_FUNC_INFO << "Invalid condition: " << condition;
                return false;
            }

            QString addr = condition.split(" ")[0];
            QStringList splt = addr.split("/");

            // Get the corresponding device
            if(!instance().hasDevice(splt[1]))
            {
                qDebug() << Q_FUNC_INFO << "Device '" << splt[1] << "' not found";
                return false;
            }
            auto dev = instance().device(splt[1]);

            return dev->check(condition);
        }

        static void sendMessage(const QString& address, QVariant val)
        {
            // TODO thorought testing required
            if(address.isEmpty())
            {
                qDebug() << Q_FUNC_INFO << "Invalid address: " << address;
                return;
            }

            // Get the first part of the address
            QStringList splt = address.split("/");

            // Get the corresponding device
            if(!instance().hasDevice(splt[1]))
            {
                qDebug() << Q_FUNC_INFO << "Device '" << splt[1] << "' not found";
                return;
            }
            auto dev = instance().device(splt[1]);

            // Remove two first elements
            splt.removeFirst();
            splt.removeFirst();

            Message m;
            m.address = splt.join("/");
            m.value = val;
            dev->sendMessage(m);
        }

        static void sendMessage(const Message& m)
        {
            sendMessage(m.address, m.value);
        }

    private:
        static DeviceList m_instance;
};

class DeviceExplorerPlugin :
    public QObject,
    public iscore::PanelFactoryInterface_QtInterface,
    public iscore::FactoryFamily_QtInterface,
    public iscore::FactoryInterface_QtInterface
{
        Q_OBJECT
        Q_PLUGIN_METADATA(IID PanelFactoryInterface_QtInterface_iid)
        Q_INTERFACES(
                iscore::PanelFactoryInterface_QtInterface
                iscore::FactoryFamily_QtInterface
                iscore::FactoryInterface_QtInterface)

    public:
        DeviceExplorerPlugin();
        virtual ~DeviceExplorerPlugin() = default;

        // Panel interface
        virtual QStringList panel_list() const override;
        virtual iscore::PanelFactoryInterface* panel_make(QString name) override;


        // Factory for protocols
        virtual QVector<iscore::FactoryFamily> factoryFamilies_make() override;

        // Contains the OSC, MIDI, Minuit factories
        virtual QVector<iscore::FactoryInterface*> factories_make(QString factoryName) override;

    private:
        SingletonProtocolList m_protocols;

};
