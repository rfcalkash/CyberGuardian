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

    // Connections{
    //     target: terrain
    //     function onMapsChanged(){
    //         terrainLoader.active=false
    //         terrainLoader.active=true
    //     }
    // }

    // Component.onCompleted: {
    //     terrain.generatePixmaps();
    // }

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
            visible: true
            id: sphereId
            source: "#Sphere"
            position: Qt.vector3d(10,100,10)
            materials: [
                DefaultMaterial {
                    diffuseColor: Qt.rgba(0.8, 0.6, 0.4, 1.0)
                }
            ]
        }

        // Repeater3D{
        //     id: terrainData
        //     property var chunksAmount: Qt.size(10,10)
        //     property var chunkSize: Qt.size(100,100)
        //     property double exp: mountainsSlider.value
        //     property int seed: seedId.value
        //     model: StaticQmlHelper.rebuildChunksModel(chunksAmount,chunkSize)
        //     delegate: Model{
        //         pickable: true
        //         geometry: TerrainGeometry{
        //             chunksSize: terrainData.chunksAmount
        //             requestedRect: modelData.rect
        //             exp: terrainData.exp
        //             seed: terrainData.seed
        //             onTerrainUpdated: {
        //                 update()
        //                 cameraId.rotate(1,Qt.vector3d(0,1,0),Node.SceneSpace)
        //                 cameraId.rotate(-1,Qt.vector3d(0,1,0),Node.SceneSpace)
        //             }
        //         }
        //         position: modelData.position
        //         materials: [ PrincipledMaterial {
        //                 metalness: 0.0
        //                 roughness: 1.0
        //                 baseColor: StaticQmlHelper.fromTerrainType(mainWindow.terrainType)
        //                 // lighting: PrincipledMaterial.NoLighting
        //             } ]
        //         // scale: Qt.vector3d(100,100,100)
        //     }
        // }

    }
    WasdController{
        controlledObject: cameraId
        // mouseEnabled: false
    }
    ColumnLayout{
        anchors.right: parent.right
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
        // Slider{
        //     id:mountainsSlider
        //     from:1
        //     to:20
        //     value: 3
        // }
        // SpinBox{
        //     id: seedId
        //     from: 0
        //     to: 100000
        //     value: 0
        // }
        Button{
            text: "Show sphere"
            onClicked: cameraId.lookAt(sphereId)
        }
    }

    DebugView{
        source: sceneId
    }

}
