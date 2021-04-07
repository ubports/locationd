
#include <QCoreApplication>
#include <memory>
#include <QTimer>

#include "dbusdatatypes.h"
#include "sessionInterface.h"
#include "serviceInterface.h"


int main(int argc, char **argv) {
    QCoreApplication a(argc, argv);


    DbusDataTypes::registerMetaType();

    auto sess = std::make_shared<core::locationd::Service>("core.locationd.Service",
                                                                    "/core/locationd/Service",
                                                                    QDBusConnection::systemBus(), &a);

    requirements req;
    req.insert("wants-heading", true);
    req.insert("wants-position", true);
    auto sessrep = sess->CreateSessionForCriteria(req);
    sessrep.waitForFinished();
    auto val = sessrep.value();

    qWarning() << val.path();
    auto session = std::make_shared<core::locationd::Session>("core.locationd.Service",
                                                                    val.path(),
                                                                    QDBusConnection::systemBus(), &a);
    auto prop = std::make_shared<org::freedesktop::DBus::Properties>("core.locationd.Service",
                                                                    val.path(),
                                                                    QDBusConnection::systemBus(), &a);

    qWarning() << sess->state() << sess->isOnline();
    session->StartHeadingUpdates().waitForFinished();
    session->StartPositionUpdates().waitForFinished();

    QObject::connect(prop.get(), &org::freedesktop::DBus::Properties::PropertiesChanged, &a, [&](const QString &interface, const QVariantMap &changed, const QStringList &invalid){
        auto pos = qdbus_cast< Position >(changed["Position"].value<QDBusArgument>());
        qWarning() << pos.time() << pos.value();

/*
        uint time;
        QMap<QString, qreal> map;
        auto argument = changed["Position"].value<QDBusArgument>();
        argument.beginStructure();
        argument >> time;
        argument >> map;
        argument.endStructure();
        qWarning() << map << time;

        uint time2;
        QMap<QString, qreal> map2;
        auto argument2 = changed["Position"].value<QDBusArgument>();
        argument2.beginStructure();
        argument2 >> map2;
        argument2 >> time2;
        argument2.endStructure();
        qWarning() << map2 << time2;

     //   auto pos2 = session->position();
      //  qWarning() << pos2.time() << pos2.value();

/*
        auto head = session->heading();
        qWarning() << head.value() << head.time();

        auto pos = session->position();
        qWarning() << pos.time() << head.value();
        */
    });

    a.exec();
}
