/*
 * Copyright 2020 UBports foundation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Marius Gripsgard <marius@ubports.com>
 */

#pragma once

#include <QtPositioning/QGeoPositionInfoSourceFactory>
#include <memory>

#include "dbusdatatypes.h"
#include "sessionInterface.h"
#include "serviceInterface.h"

namespace core
{
    /*
namespace locationd
{
class Service;
class Session;
}
*/
class GeoPositionInfoSource : public QGeoPositionInfoSource
{
    Q_OBJECT
public:
    GeoPositionInfoSource(QObject *parent = 0);
    ~GeoPositionInfoSource();

    // From QGeoPositionInfoSource
    void setUpdateInterval(int msec);
    QGeoPositionInfo lastKnownPosition(bool fromSatellitePositioningMethodsOnly = false) const;
    PositioningMethods supportedPositioningMethods() const;
    void setPreferredPositioningMethods(PositioningMethods methods);
    int minimumUpdateInterval() const;

    Error error() const;

    // Updates request state
    enum State {
        stopped = 0,
        running,
        one_shot,
        suspended,
    };

public slots:
    void applicationStateChanged();
    virtual void startUpdates();
    virtual void stopUpdates();
    virtual void requestUpdate(int timeout = 5000);
    void timeout();

private:
    std::shared_ptr<locationd::Service> m_serviceInterface;
    std::shared_ptr<locationd::Session> m_sessionInterface;

    bool m_applicationActive;
    int m_lastReqTimeout;
    int m_state;
};
}
