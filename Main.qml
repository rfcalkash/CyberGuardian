import QtQuick
import QtQuick3D
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick3D.Helpers
import CyberGuardian

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("CyberGuardian")
    id: mainWindow
    property int terrainType:terrainTypeCB.currentValue

    Connections{
        target: terrain
        function onMapsChanged(){
            terrainLoader.active=false
            terrainLoader.active=true
        }
    }

    Component.onCompleted: {
        terrain.generatePixmaps();
    }

    View3D{
        id: sceneId
        anchors.fill: parent
        camera: PerspectiveCamera{
            id: cameraId
            position: Qt.vector3d(0, 200, 300)
            eulerRotation.x: -30
            fieldOfView: 90
            fieldOfViewOrientation: PerspectiveCamera.Horizontal
        }
        environment: SceneEnvironment {
            backgroundMode: SceneEnvironment.Color
            clearColor: StaticQmlHelper.fromTerrainType(mainWindow.terrainType)
            antialiasingMode: SceneEnvironment.ProgressiveAA

            antialiasingQuality: SceneEnvironment.VeryHigh
            // temporalAAEnabled: true
        }
        DirectionalLight {
            id: light1
            color: Qt.rgba(1.0, 1.0, 1.0, 1.0)
            ambientColor: Qt.rgba(0.1, 0.1, 0.1, 1.0)
            position: Qt.vector3d(0, 200, 0)
            eulerRotation.x:-60
            eulerRotation.y: sunPos.value
            visible: true
            castsShadow: true
            shadowMapQuality: Light.ShadowMapQualityVeryHigh
        }
        Model{
            id: sphereId
            source: "#Sphere"
            position: Qt.vector3d(10,100,10)
            materials: [
                DefaultMaterial {
                    diffuseColor: Qt.rgba(0.8, 0.6, 0.4, 1.0)
                }
            ]
        }
        Loader{
            id: terrainLoader
            sourceComponent: Model {
                scale: Qt.vector3d(100, 100, 100)
                geometry: HeightFieldGeometry {
                    id: terrainGeometry
                    source: "images/earth.png"
                    extents: Qt.vector3d(400,10,400)
                }
                materials: [ DefaultMaterial { } ]
            }
        }

    }
    WasdController{
        controlledObject: cameraId
        // mouseEnabled: false
    }
    ColumnLayout{
        ComboBox{
            id: terrainTypeCB
            model: ListModel {
                id: model
                ListElement {
                    text: "Desert"
                    value: CGEnums.Desert}
                ListElement {
                    text: "Snow"
                    value: CGEnums.Snow}
                ListElement {
                    text: "Grass"
                    value: CGEnums.Grass}
            }
            textRole: "text"
            valueRole: "value"
        }
        Slider{
            id:sunPos
            from:0
            to:360
            PropertyAnimation{
                loops: Animation.Infinite
                from: 0
                to: 360
                duration: 10000
                target: sunPos;
                property: "value";
                running: autorotateCB.checked
            }
        }
        CheckBox{
            id: autorotateCB
            text: "Autorotate sun"
        }
        Rectangle{
            Layout.fillWidth: true
            height: childrenRect.height
            Text {
                text: qsTr("FPS:")+sceneId.renderStats.fps
            }
        }
    }

}
