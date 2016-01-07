# Simple QObject serialization/deserialization library.

This library allowes to serialize and deserialize properties of object of class derived from QObject with a single function call:

1. Serialize object state with a single call:
```
QDomNode serializedObjectProperties = serialize (
  this,
  QObjectSerialization::TAG_OBJECT_NAME);
```
serializedObjectProperties will be XML DOM element with tag name that's the same as object name stored in objectName property.
2. Save serialized object state in XML file like this:
```
 <SomeWidget minimumHeight="0" toolTipDuration="-1" modal="false" focus="false" windowOpacity="1" styleSheet="" objectName="SomeWidget" autoFillBackground="true" windowModified="false" maximized="false" toolTip="" inputMethodHints="0" minimumWidth="0" isActiveWindow="false" height="1024" y="51" width="1280" accessibleDescription="" windowTitle="" enabled="true" font="MS Shell Dlg 2,8.25,-1,5,50,0,0,0,0,0" windowModality="0" statusTip="" contextMenuPolicy="1" fullScreen="true" accessibleName="" maximumWidth="16777215" visible="true" x="-1280" updatesEnabled="true" maximumHeight="16777215" mouseTracking="true" layoutDirection="0" windowFilePath="" focusPolicy="0" whatsThis="" acceptDrops="false" windowIconText="" minimized="false">
        <property name="childrenRect">
          <QRect y="0" width="0" x="0" height="0"/>
        </property>
        <property name="geometry">
          <QRect y="51" width="1280" x="-1280" height="1024"/>
        </property>
        <property name="normalGeometry">
          <QRect y="358" width="640" x="-1050" height="480"/>
        </property>
        <property name="frameGeometry">
          <QRect y="51" width="1280" x="-1280" height="1024"/>
        </property>
        <property name="rect">
          <QRect y="0" width="1280" x="0" height="1024"/>
        </property>
      </SomeWidget>
```
3. Restore full object state with a single call:
```
deserialize (
  window,
  serializedObjectProperties);
```

The library provides support for serialization/deserialization of eather properties that can be stored as QString by default or properties that can not be stored as QString. For this purpose custom serializers/deserializers are implemented. For now only QRect, QRectF and QStringList can be serialized this way, however any other Qt and user defined types support can be added.