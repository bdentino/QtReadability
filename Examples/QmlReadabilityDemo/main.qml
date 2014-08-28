import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
import Qtino.Readability 1.0

Window {
    id: rootWindow

    signal urlChanged(string url);

    ReadabilityParserApi {
        id: parserApi
        version: "v1"
        token: "91de23430430c02b53345cb6b4bb9e5fe5257f35"
    }

    ReadabilityConfidence {
        id: confidenceObject
        api: parserApi
        url: urlInput.text
    }

    ReadabilityArticle {
        id: articleObject
        api: parserApi
        url: urlInput.text
    }

    visible: true
    width: 500
    height: 800

    color: 'darkgrey'

    Rectangle {
        id: urlInputBackground
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 20
        height: 50
        radius: 20
        color: 'lightgrey'
        TextInput {
            id: urlInput
            anchors.left: parent.left
            anchors.right: parent.right
            height: parent.height
            anchors.leftMargin: 20
            anchors.rightMargin: 20
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: height * 0.4
            clip: true
        }
        Text {
            id: defaultText
            text: 'Enter a URL'
            font.italic: true
            font.pixelSize: urlInput.font.pixelSize
            color: rootWindow.color
            anchors.verticalCenter: urlInput.verticalCenter
            anchors.left: urlInput.left
            visible: urlInput.text === ""
        }
    }

    Rectangle {
        id: imageBackground
        color: 'grey'
        height: 150
        anchors {
            left: parent.left
            right: parent.right
            top: urlInputBackground.bottom
            margins: 20
        }
        radius: 20

        Image {
            id: leadImage
            anchors.fill: parent
            source: articleObject.leadImageSource;
        }

        Rectangle {
            id: imageLabel
            anchors {
                top: parent.top
                right: parent.right
                margins: 10
            }
            color: '#88cccccc'
            height: 30
            width: 100
            radius: 15
            Text { anchors.centerIn: parent; text: "Lead Image" }
        }

        opacity: errorPopup.visible ? 0.5 : 1.0
    }

    Rectangle {
        id: contentArea
        color: 'lightgrey'
        radius: 10
        anchors {
            top: imageBackground.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
            margins: 20
        }

        TextArea {
            id: content
            textFormat: Text.RichText
            text: articleObject.htmlContent
            anchors.margins: 10
            anchors.fill: parent
            wrapMode: Text.WordWrap
            backgroundVisible: false
            frameVisible: false
        }

        Rectangle {
            id: contentLabel
            anchors {
                top: parent.top
                right: parent.right
                margins: 10
            }
            color: "#88666666"
            height: 30
            width: 100
            radius: 15
            Text { anchors.centerIn: parent; text: "Content" }
            z: content.z + 1
        }
        opacity: errorPopup.visible ? 0.5 : 1.0
    }

    Rectangle {
        id: errorPopup
        anchors.centerIn: parent
        height: 200
        width: parent.width - 60
        radius: 20
        color: '#bb440000'
        Text {
            id: errorTitle
            text: "Readability Error!"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.margins: 10
            color: 'white'
            font.bold: true;
            font.pointSize: 20
        }
        Text {
            id: errorMessage
            anchors.top: errorTitle.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 20

            wrapMode: Text.WordWrap
            color: 'white'
            font.pointSize: 16

            text: articleObject.error
        }

        visible: opacity !== 0
        opacity: (errorMessage.text === "" || urlInput.text === "") ? 0 : 1
    }
}
