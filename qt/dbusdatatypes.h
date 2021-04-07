#pragma once

#include <QTime>
#include <QMap>
#include <QtDBus>

template<typename T>
class Update
{
public:
    inline Update() : m_value{}, m_when{}
    {
    }
    inline bool operator==(const Update<T>& rhs) const
    {
        return m_value == rhs.m_value && m_when == rhs.m_when;
    }

    inline bool operator!=(const Update<T>& rhs) const
    {
        return !(m_value == rhs.m_value && m_when == rhs.m_when);
    }

    inline friend QDBusArgument &operator<<(QDBusArgument &argument, const Update &update)
    {
        qWarning("ARR");
        argument.beginStructure();
        argument << update.m_when;
        argument << update.m_value;
        argument.endStructure();

    return argument;
    }

    inline friend const QDBusArgument &operator>>(const QDBusArgument &argument, Update &update)
    {
        qWarning("BAAAH");
        argument.beginStructure();
        argument >> update.m_when;
        argument >> update.m_value;
        argument.endStructure();

        return argument;
    }

    inline T value() {
        return m_value;
    }

    inline QDateTime time() {
        qWarning() << m_when;
        return QDateTime::fromMSecsSinceEpoch(m_when);
    }

private:
    T m_value;
    int m_when;
};

// Service
typedef QMap<QString, QVariant> requirements;
typedef QMap<QString, QVariant> VisibleSpaceVehicles;

// Session
typedef Update<QMap<QString, double>> Position;
typedef Update<qreal> Velocity;
typedef Update<qreal> Heading;

Q_DECLARE_METATYPE(requirements)

Q_DECLARE_METATYPE(Position)
Q_DECLARE_METATYPE(Velocity)

/*
class Position
{
public:
    inline Position() : m_value{}, m_when{}
    {
    }
    inline bool operator==(const Position& rhs) const
    {
        return m_value == rhs.m_value && m_when == rhs.m_when;
    }

    inline bool operator!=(const Position& rhs) const
    {
        return !(m_value == rhs.m_value && m_when == rhs.m_when);
    }

    friend QDBusArgument &operator<<(QDBusArgument &argument, const Position &update)
    {
        qWarning("Graaah");
        argument.beginStructure();
        argument << update.m_when;
        argument << update.m_value;
        argument.endStructure();

    return argument;
    }

    friend const QDBusArgument &operator>>(const QDBusArgument &argument, Position &update)
    {
        qWarning("BAAAH");
        argument.beginStructure();
        argument >> update.m_when;
        argument >> update.m_value;
        argument.endStructure();

        return argument;
    }

    inline QMap<QString, qreal> value() {
        return m_value;
    }

    inline QDateTime time() {
        return QDateTime::fromMSecsSinceEpoch(m_when);
    }

private:
    QMap<QString, qreal> m_value;
    uint m_when;
};

Q_DECLARE_METATYPE(Position)
*/

namespace DbusDataTypes{
inline void registerMetaType() {
    qRegisterMetaType<Position>("Position");
    qDBusRegisterMetaType<Position>();
    qRegisterMetaType<Velocity>("Velocity");
    qDBusRegisterMetaType<Velocity>();
    qRegisterMetaType<Heading>("Heading");
    qDBusRegisterMetaType<Heading>();
}
}
