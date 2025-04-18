# Resource object code (Python 3)
# Created by: object code
# Created by: The Resource Compiler for Qt version 6.6.3
# WARNING! All changes made in this file will be lost!

from PySide6 import QtCore

qt_resource_data = b"\
\x00\x00\x0b3\
\xef\
\xbb\xbf// import QtQu\
ick 2.15\x0d\x0a\x0d\x0a// I\
tem {\x0d\x0a\x0d\x0a// }\x0d\x0a\x0d\
\x0aimport QtQuick\x0d\
\x0aimport QtLocati\
on\x0d\x0aimport QtPos\
itioning\x0d\x0a\x0d\x0aRect\
angle {\x0d\x0a    wid\
th: Qt.platform.\
os == \x22android\x22 \
? Screen.width :\
 512\x0d\x0a    height\
: Qt.platform.os\
 == \x22android\x22 ? \
Screen.height : \
512\x0d\x0a    visible\
: true\x0d\x0a    // t\
itle: map.center\
 + \x22 zoom \x22 + ma\
p.zoomLevel.toFi\
xed(3)\x0d\x0a    //  \
      + \x22 min \x22 \
+ map.minimumZoo\
mLevel + \x22 max \x22\
 + map.maximumZo\
omLevel\x0d\x0a\x0d\x0a    P\
lugin {\x0d\x0a       \
 id: mapPlugin\x0d\x0a\
        name: \x22o\
sm\x22\x0d\x0a\x0d\x0a        /\
/ PluginParamete\
r { name: \x22osm.m\
apping.providers\
repository.addre\
ss\x22; value: \x22htt\
p://www.mywebsit\
e.com/osm_reposi\
tory\x22 }\x0d\x0a       \
 // PluginParame\
ter { name: \x22osm\
.mapping.highdpi\
_tiles\x22; value: \
true }\x0d\x0a\x0d\x0a\x0d\x0a    \
}\x0d\x0a\x0d\x0a    Map {\x0d\x0a\
        id: map\x0d\
\x0a        anchors\
.fill: parent\x0d\x0a \
       plugin: m\
apPlugin\x0d\x0a      \
  center: QtPosi\
tioning.coordina\
te(35.4265777, 1\
19.456549) // Os\
lo\x0d\x0a        zoom\
Level: 14\x0d\x0a     \
   property geoC\
oordinate startC\
entroid\x0d\x0a\x0d\x0a     \
   activeMapType\
: supportedMapTy\
pes[1] // Cycle \
map provided by \
Thunderforest\x0d\x0a\x0d\
\x0a\x0d\x0a        Pinch\
Handler {\x0d\x0a     \
       id: pinch\
\x0d\x0a            ta\
rget: null\x0d\x0a    \
        onActive\
Changed: if (act\
ive) {\x0d\x0a        \
        map.star\
tCentroid = map.\
toCoordinate(pin\
ch.centroid.posi\
tion, false)\x0d\x0a  \
          }\x0d\x0a   \
         onScale\
Changed: (delta)\
 => {\x0d\x0a         \
       map.zoomL\
evel += Math.log\
2(delta)\x0d\x0a      \
          map.al\
ignCoordinateToP\
oint(map.startCe\
ntroid, pinch.ce\
ntroid.position)\
\x0d\x0a            }\x0d\
\x0a            onR\
otationChanged: \
(delta) => {\x0d\x0a  \
              ma\
p.bearing -= del\
ta\x0d\x0a            \
    map.alignCoo\
rdinateToPoint(m\
ap.startCentroid\
, pinch.centroid\
.position)\x0d\x0a    \
        }\x0d\x0a     \
       grabPermi\
ssions: PointerH\
andler.TakeOverF\
orbidden\x0d\x0a      \
  }\x0d\x0a        Whe\
elHandler {\x0d\x0a   \
         id: whe\
el\x0d\x0a            \
// workaround fo\
r QTBUG-87646 / \
QTBUG-112394 / Q\
TBUG-112432:\x0d\x0a  \
          // Mag\
ic Mouse pretend\
s to be a trackp\
ad but doesn't w\
ork with PinchHa\
ndler\x0d\x0a         \
   // and we don\
't yet distingui\
sh mice and trac\
kpads on Wayland\
 either\x0d\x0a       \
     acceptedDev\
ices: Qt.platfor\
m.pluginName ===\
 \x22cocoa\x22 || Qt.p\
latform.pluginNa\
me === \x22wayland\x22\
\x0d\x0a              \
               ?\
 PointerDevice.M\
ouse | PointerDe\
vice.TouchPad\x0d\x0a \
                \
            : Po\
interDevice.Mous\
e\x0d\x0a            r\
otationScale: 1/\
120\x0d\x0a           \
 property: \x22zoom\
Level\x22\x0d\x0a        \
}\x0d\x0a        DragH\
andler {\x0d\x0a      \
      id: drag\x0d\x0a\
            targ\
et: null\x0d\x0a      \
      onTranslat\
ionChanged: (del\
ta) => map.pan(-\
delta.x, -delta.\
y)\x0d\x0a        }\x0d\x0a \
       Shortcut \
{\x0d\x0a            e\
nabled: map.zoom\
Level < map.maxi\
mumZoomLevel\x0d\x0a  \
          sequen\
ce: StandardKey.\
ZoomIn\x0d\x0a        \
    onActivated:\
 map.zoomLevel =\
 Math.round(map.\
zoomLevel + 1)\x0d\x0a\
        }\x0d\x0a     \
   Shortcut {\x0d\x0a \
           enabl\
ed: map.zoomLeve\
l > map.minimumZ\
oomLevel\x0d\x0a      \
      sequence: \
StandardKey.Zoom\
Out\x0d\x0a           \
 onActivated: ma\
p.zoomLevel = Ma\
th.round(map.zoo\
mLevel - 1)\x0d\x0a   \
     }\x0d\x0a    }\x0d\x0a}\
\x0d\x0a\
"

qt_resource_name = b"\
\x00\x08\
\x08\x01Z\x5c\
\x00m\
\x00a\x00i\x00n\x00.\x00q\x00m\x00l\
"

qt_resource_struct = b"\
\x00\x00\x00\x00\x00\x02\x00\x00\x00\x01\x00\x00\x00\x01\
\x00\x00\x00\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\
\x00\x00\x01\x96F\x90\xc4H\
"

def qInitResources():
    QtCore.qRegisterResourceData(0x03, qt_resource_struct, qt_resource_name, qt_resource_data)

def qCleanupResources():
    QtCore.qUnregisterResourceData(0x03, qt_resource_struct, qt_resource_name, qt_resource_data)

qInitResources()
