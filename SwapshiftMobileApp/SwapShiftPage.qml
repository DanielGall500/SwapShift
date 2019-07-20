import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12


Item {
    width: 400
    height: 400


    Column {

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter


        Label {
            id: chooseShiftLab
            width: 239
            height: 30
            text: "Choose the shift you want to swap"
            font.pointSize: 11
            font.capitalization: Font.MixedCase
        }

        ComboBox {
            id: chooseShiftCombo
            height: 40
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 8

            model: chooseShiftModel

            textRole: "display"

            onCurrentIndexChanged: {
                
                availEmployeeFinder.set_shift_indx(chooseShiftCombo.currentIndex);
                finderModel.setEmplList(availEmployeeFinder.get_available_empl());
                
            }
        }

        ComboBox {
            id: availEmplCombo
            model: finderModel
            textRole: "display"
        }
    }

}
