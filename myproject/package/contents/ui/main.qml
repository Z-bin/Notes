import QtQuick.Window 2.15
import QtQuick 2.12
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.5 as QQC2

import org.kde.kirigami 2.5 as Kirigami
import org.kde.kcm 1.2 as KCM

import org.kde.colorcorrect 0.1 as CC
KCM.SimpleKCM {
    id: root
    property int error: cA.error
    property bool defaultRequested: false
    implicitHeight: Kirigami.Units.gridUnit * 29
    implicitWidth: Kirigami.Units.gridUnit * 35 
   
       Kirigami.FormLayout {
       Text {
          text: "ddd"
       }
    }

}
