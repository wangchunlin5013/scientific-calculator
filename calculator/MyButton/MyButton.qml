import QtQuick 2.0

Rectangle {
    id:mybutton

    property string value:""

    signal clicked(string value)

    anchors.leftMargin: 5
    anchors.topMargin: 5
    width: 50
    height: 30
    border.color: "black"
    border.width: 1



    Text {
        id: buttontext
        anchors.centerIn: parent

        text:value
        color: "black"
        font.pointSize:12
        font.bold: true
    }

    ColorAnimation{
        id:buttonanimation
        target: mybutton
        property: "color"
        from: "gray"
        to: "white"
        duration: 200
    }

    MouseArea{
        id:buttonmouse
        anchors.fill: parent
        onClicked:
        {
            buttonanimation.start()
            mybutton.clicked(value)
        }
    }
}
