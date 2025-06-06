#!/bin/bash
FILE=appleIIlogo.png
mkdir MyIcon.iconset
sips -z 16 16     $FILE --out MyIcon.iconset/icon_16x16.png
sips -z 32 32     $FILE --out MyIcon.iconset/icon_16x16@2x.png
sips -z 32 32     $FILE --out MyIcon.iconset/icon_32x32.png
sips -z 64 64     $FILE --out MyIcon.iconset/icon_32x32@2x.png
sips -z 128 128   $FILE --out MyIcon.iconset/icon_128x128.png
sips -z 256 256   $FILE --out MyIcon.iconset/icon_128x128@2x.png
sips -z 256 256   $FILE --out MyIcon.iconset/icon_256x256.png
sips -z 512 512   $FILE --out MyIcon.iconset/icon_256x256@2x.png
sips -z 512 512   $FILE --out MyIcon.iconset/icon_512x512.png
cp $FILE MyIcon.iconset/icon_512x512@2x.png
iconutil -c icns --output gs2.icns MyIcon.iconset
