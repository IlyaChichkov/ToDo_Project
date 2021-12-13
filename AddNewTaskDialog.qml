import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item{
    visible: true
    width: 300
    height: 300
    ColumnLayout {
        anchors.fill: parent
                ColumnLayout{
                        Label{
                            text: "Имя задачи"
                        }

                        TextField{
                            id: taskName
                            Layout.fillWidth: true
                        }
                }
                ColumnLayout{
                        Label{
                            text: "Описание задачи"
                        }
                        TextField{
                            id: taskDesc
                            Layout.minimumHeight: 100
                            Layout.fillWidth: true

                        }
                }

                ColumnLayout{
                    Rectangle{
                        id: calendar
                        function formatNumber(number) {
                            return number < 10 && number >= 0 ? "0" + number : number.toString()
                        }

                        RowLayout {
                            RowLayout {
                                id: rowTumbler

                                Tumbler {
                                    id: hoursTumbler
                                    model: 24
                                    delegate: Text{
                                        text: calendar.formatNumber(modelData)
                                        font: Tumbler.tumbler.font
                                        opacity: 1.0 - Math.abs(Tumbler.displacement) / (Tumbler.tumbler.visibleItemCount / 2)
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                    }
                                }
                                Tumbler {
                                    id: minutesTumbler
                                    model: 60
                                    delegate: Text{
                                        text: calendar.formatNumber(modelData)
                                        font: Tumbler.tumbler.font
                                        opacity: 1.0 - Math.abs(Tumbler.displacement) / (Tumbler.tumbler.visibleItemCount / 2)
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                    }
                                }
                            }

                            RowLayout {
                                id: datePicker

                                Layout.leftMargin: 20

                                property alias dayTumbler: dayTumbler
                                property alias monthTumbler: monthTumbler
                                property alias yearTumbler: yearTumbler

                                readonly property var days: [31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

                                Tumbler {
                                    id: dayTumbler

                                    function updateModel() {
                                        // Populate the model with days of the month. For example: [0, ..., 30]
                                        var previousIndex = dayTumbler.currentIndex
                                        var array = []
                                        var newDays = datePicker.days[monthTumbler.currentIndex]
                                        for (var i = 1; i <= newDays; ++i)
                                            array.push(i)
                                        dayTumbler.model = array
                                        dayTumbler.currentIndex = Math.min(newDays - 1, previousIndex)
                                    }

                                    Component.onCompleted: updateModel()

                                    delegate: Text{
                                        text: calendar.formatNumber(modelData)
                                        font: Tumbler.tumbler.font
                                        opacity: 1.0 - Math.abs(Tumbler.displacement) / (Tumbler.tumbler.visibleItemCount / 2)
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                    }
                                }
                                Tumbler {
                                    id: monthTumbler

                                    onCurrentIndexChanged: dayTumbler.updateModel()

                                    model: ListModel {
                                        ListElement { name: "Январь" }
                                        ListElement { name: "Февраль" }
                                        ListElement { name: "Март" }
                                        ListElement { name: "Апрель" }
                                        ListElement { name: "Май" }
                                        ListElement { name: "Июнь" }
                                        ListElement { name: "Июль" }
                                        ListElement { name: "Август" }
                                        ListElement { name: "Сентябрь" }
                                        ListElement { name: "Октрябрь" }
                                        ListElement { name: "Ноябрь" }
                                        ListElement { name: "Декабрь" }

                                    }

                                    delegate: Text{
                                        text: calendar.formatNumber(modelData)
                                        font: Tumbler.tumbler.font
                                        opacity: 1.0 - Math.abs(Tumbler.displacement) / (Tumbler.tumbler.visibleItemCount / 2)
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                    }
                                }
                                Tumbler {
                                    id: yearTumbler

                                    // This array is populated with the next three years. For example: [2018, 2019, 2020]
                                    readonly property var years: (function() {
                                        var currentYear = new Date().getFullYear()
                                        return [0, 1, 2].map(function(value) { return value + currentYear; })
                                    })()

                                    model: years
                                    delegate: Text{
                                        text: calendar.formatNumber(modelData)
                                        font: Tumbler.tumbler.font
                                        opacity: 1.0 - Math.abs(Tumbler.displacement) / (Tumbler.tumbler.visibleItemCount / 2)
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                    }
                                }
                            }
                        }
                    }
                }
                RowLayout{
                    Button{
                        id: create
                        text: "Создать"
                        onClicked: createClicked()
                    }
                    Button{
                        id: cancel
                        text: "Отменить"
                        onClicked: cancelClicked()
                    }

                    Layout.alignment: Qt.AlignRight | Qt.AlignBottom
                }
                anchors.margins: 10
    }

    signal createClicked()
    signal cancelClicked()

    onCreateClicked: (() => {
                          // addNewTask введён mainwindow как контекст
                          addNewTask.onCreateClicked([taskName.text,
                                                      taskDesc.text,
                                                      hoursTumbler.currentIndex,
                                                      minutesTumbler.currentIndex,
                                                     dayTumbler.currentIndex + 1,
                                                     ])
//                          addNewTask.destruct();
//                          console.log(monthTumbler.currentItem)
                      })()
    onCancelClicked: (() => {
                          addNewTask.destruct();
                      })()
}
