#pragma once
#include <Device/Protocol/DeviceSettings.hpp>
#include <Device/Protocol/ProtocolSettingsWidget.hpp>

#include <QNetworkAccessManager>
#include <QNetworkRequest>

class ZeroconfBrowser;
class QLineEdit;
class QSpinBox;
class QWidget;

namespace Engine
{
namespace Network
{
class OSCQueryProtocolSettingsWidget final
    : public Device::ProtocolSettingsWidget
{
public:
  OSCQueryProtocolSettingsWidget(QWidget* parent = nullptr);

  Device::DeviceSettings getSettings() const override;

  void setSettings(const Device::DeviceSettings& settings) override;

protected:
  void setDefaults();

protected:
  QLineEdit* m_deviceNameEdit{};
  QLineEdit* m_localHostEdit{};

  ZeroconfBrowser* m_browser{};
  QNetworkAccessManager m_http_client;
  QNetworkReply* m_cur_reply{};
};
}
}
