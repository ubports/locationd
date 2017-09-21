import sys
import dbus
from dbus.mainloop.glib import DBusGMainLoop
import gobject

dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
bus = dbus.SystemBus()

service = dbus.Interface(
  bus.get_object("com.ubuntu.location.Service", "/com/ubuntu/location/Service"),
  "com.ubuntu.location.Service")

requirements = dict()
# Sign up for position updates only. We're not interested in
# updates for heading or velocity.
requirements["wants-position"] = True
session_path = service.CreateSessionForCriteria(requirements)
if not session_path:
  print("ERROR: Failed to create session with locationd")
  sys.exit(1)

def session_properties_changed(properties):
  print("Got update from session:")
  for p in properties:
    print("%s = %s" % (p, properties[p]))

bus.add_signal_receiver(session_properties_changed,
                        path=session_path,
                        dbus_interface="com.ubuntu.location.Session",
                        signal_name="PropertyChanged")

session = dbus.Interface(
  bus.get_object("com.ubuntu.location.Service", session_path),
  "com.ubuntu.location.Service.Session")
session.StartPositionUpdates()

gobject.MainLoop().run()
