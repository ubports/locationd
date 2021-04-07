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

#include "qgeopositioninfosourcefactory_locationd.h"
#include "qgeopositioninfosource_locationd.h"

QGeoPositionInfoSource *core::GeoPositionInfoSourceFactory::positionInfoSource(QObject *parent)
{
    core::GeoPositionInfoSource *src = new core::GeoPositionInfoSource(parent);
    return src;
}

QGeoSatelliteInfoSource *core::GeoPositionInfoSourceFactory::satelliteInfoSource(QObject *parent)
{
    Q_UNUSED(parent);
    return 0;
}

QGeoAreaMonitorSource *core::GeoPositionInfoSourceFactory::areaMonitor(QObject *parent)
{
    Q_UNUSED(parent);
    return 0;
}
