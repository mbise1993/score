#include "ArtnetSpecificSettings.hpp"

#include <score/serialization/DataStreamVisitor.hpp>
#include <score/serialization/JSONVisitor.hpp>

#include <QJsonObject>
#include <QJsonValue>
#include <QString>

template <>
void DataStreamReader::read(const Engine::Network::ArtnetSpecificSettings& n)
{
  insertDelimiter();
}

template <>
void DataStreamWriter::write(Engine::Network::ArtnetSpecificSettings& n)
{
  checkDelimiter();
}

template <>
void JSONObjectReader::read(const Engine::Network::ArtnetSpecificSettings& n)
{
}

template <>
void JSONObjectWriter::write(Engine::Network::ArtnetSpecificSettings& n)
{
}
