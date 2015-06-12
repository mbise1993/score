#pragma once
#include <QString>
#include <QJsonObject>
#include <QModelIndex>


#include <State/Message.hpp>


class QObject;
class DeviceExplorerModel;
namespace iscore
{
    class Document;
}

namespace DeviceExplorer
{
    QString panelName();
    QString explorerName();

    Address addressFromModelIndex(const QModelIndex& index);
    Message messageFromModelIndex(const QModelIndex& index);
}
