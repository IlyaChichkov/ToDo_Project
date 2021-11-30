import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window{
    visible: true
    width: 300
    height: 300
    ColumnLayout {
        anchors.fill: parent
        RowLayout{
        Layout.alignment: Qt.AlignTop
            ColumnLayout{
                RowLayout{
                    Label{
                        text: "Имя задачи"
                    }

                }
                RowLayout{
                    TextField{
                        id: taskName
                        Layout.fillWidth: true
                    }
                }
            }
        }
        RowLayout{
            Button{
                id: create
                text: "Создать"

            }
            Button{
                id: cancel
                text: "Отменить"

            }
            signal createClicked(string text)
            Layout.alignment: Qt.AlignRight | Qt.AlignBottom
            Layout.margins: 10
        }
    }

}


