import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    visible: true
    width: 400
    height: 500
    title: qsTr("SwapShift")

    StackView {
        id: stackView
        initialItem: "SwapShiftPage.qml"
        anchors.fill: parent
    }

    footer: ToolBar {

        id: mainToolBar

        Row {

            anchors.centerIn: parent

            Button {
                id: viewShiftsPageButton
                text: "My Shifts"

                onClicked: {
                    highlighted = true

                   // stackView.push("MyShiftsPageForm.ui.qml")

                }

                onActiveFocusChanged: highlighted = false
            }

            Button {
                id: swapAShiftPageButton
                text: "Swap A Shift"

                onClicked: {
                    highlighted = true
                    stackView.push("SwapShiftPage.qml")
                }

                onActiveFocusChanged: highlighted = false
            }

            Button {
                id: shiftRequestsPageButton
                text: "Requests"

                onClicked: highlighted = true
                onActiveFocusChanged: highlighted = false
            }

        }


    }
}
