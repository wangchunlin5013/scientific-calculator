import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

import "./MyButton"
Window {
    visible: true
    width: 280
    height: 400
    title: qsTr("计算器")

    flags: Qt.Dialog | Qt.MSWindowsFixedSizeDialogHint | Qt.WindowTitleHint | Qt.WindowCloseButtonHint | Qt.CustomizeWindowHint | Qt.WindowSystemMenuHint

    Rectangle{
        id:mainWindow        

        property string resultValue
        property string inputValue
        property string tempResultValue
        property string error1 : "Syntax ERROR"
        property string error2 : "Match ERROR"

        width: parent.width
        height: parent.height

        Rectangle{
            id:displayArea
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: parent.top
            anchors.topMargin: 5

            width: parent.width - 10
            height: 50

            border.color: "black"
            border.width: 2

            Text {
                id: displayResult
                color: "black"
                font.pointSize:12
                font.bold: true

                anchors.right: parent.right
                anchors.rightMargin: 5
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5

                text:mainWindow.resultValue
            }

            Text {
                id: displayInput
                color: "black"
                font.pointSize:12
                font.bold: true

                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: parent.top
                anchors.topMargin: 5

                text:mainWindow.inputValue
            }

            Text {
                id: displayError
                color: "black"
                font.pointSize:20
                font.bold: true

                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: parent.top
                anchors.topMargin: 5

                text: ""
                visible: false
            }
        }

        Grid{
            id:baseBtnGroup
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: displayArea.bottom
            anchors.topMargin: 5

            rows:4
            spacing: 5

            MyButton{id:number7;value:"7";}
            MyButton{id:number8;value:"8"}
            MyButton{id:number9;value:"9"}
            MyButton{id:btnDEL;value:"DEL"}
            MyButton{id:btnAC;value: "AC"}

            MyButton{id:number4;value:"4"}
            MyButton{id:number5;value:"5"}
            MyButton{id:number6;value:"6"}
            MyButton{id:btnMULTIPY;value:"X"}
            MyButton{id:btnEXCEPT;value: "÷"}

            MyButton{id:number1;value:"1"}
            MyButton{id:number2;value:"2"}
            MyButton{id:number3;value:"3"}
            MyButton{id:btnADD;value:"+"}
            MyButton{id:btnMINUS;value: "-"}

            MyButton{id:number0;value:"0"}
            MyButton{id:btnPOINT;value:"."}
            MyButton{id:btnEXP;value:"E"}
            MyButton{id:btnANS;value:"Ans"}
            MyButton{id:btnEQUAL;value: "="}
        }

        function setDisplay(value)
        {
            if(isEqual(value))
            {
                setDisplayResult(value)
            }
            else if(isNumber(value) || isSymbol(value))
            {
                setDisplayInput(value)
            }
            else if(isAC(value))
            {
                setDisplayClear(value)
            }
        }

        function setDisplayError(value)
        {
            setDisplayClear(value)
            displayError.visible = true
        }

        function setDisplayClear(value)
        {
            displayResult.text = "0"
            displayInput.text = ""
            resultValue = "0"
            inputValue = ""
            tempResultValue = "0"
            displayError.visible = false
        }

        function setDisplayResult(value)
        {
            var result = clc.getValue(displayInput.text, tempResultValue)

            if(result === error1 || result === error2)
                setDisplayError(result)
            else
            {
                displayResult.text = result
                tempResultValue = result
            }
        }

        function setDisplayInput(value)
        {
            if(!isDel(value))
                displayInput.text = displayInput.text + value
            else
            {
                var tempStr = displayInput.text
                tempStr = tempStr.substring(0, tempStr.length - 1)
                displayInput.text = tempStr
            }
        }

        function isNumber(value)
        {
            if(value >= 0 || value <= 9)
                return true
            return false
        }

        function isSymbol(value)
        {
            if(value === "X" || value === "÷" || value === "+" || value === "-"
               || value === "Ans" || value === "E" || value === "DEL" || value === ".")
                return true
            return false
        }

        function isDel(value)
        {
            if(value === "DEL")
                return true
            return false
        }

        function isAC(value)
        {
            if(value === "AC")
                return true
            return false
        }

        function isEqual(value)
        {
            if(value === "=")
                return true
            return false
        }

        Component.onCompleted: {
            number7.clicked.connect(setDisplay)
            number8.clicked.connect(setDisplay)
            number9.clicked.connect(setDisplay)
            btnDEL.clicked.connect(setDisplay)
            btnAC.clicked.connect(setDisplay)
            number4.clicked.connect(setDisplay)
            number5.clicked.connect(setDisplay)
            number6.clicked.connect(setDisplay)
            btnMULTIPY.clicked.connect(setDisplay)
            btnEXCEPT.clicked.connect(setDisplay)
            number1.clicked.connect(setDisplay)
            number2.clicked.connect(setDisplay)
            number3.clicked.connect(setDisplay)
            btnADD.clicked.connect(setDisplay)
            btnMINUS.clicked.connect(setDisplay)
            number0.clicked.connect(setDisplay)
            btnPOINT.clicked.connect(setDisplay)
            btnEXP.clicked.connect(setDisplay)
            btnANS.clicked.connect(setDisplay)
            btnEQUAL.clicked.connect(setDisplay)
        }

    }
}
