import QtQuick
import QtQuick3D

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("CyberGuardian")
    View3D{
        camera: PerspectiveCamera{
            position: Qt.vector3d(0, 200, 300)
            eulerRotation.x: -30
            fieldOfView: 90
        }
        environment: SceneEnvironment {
            antialiasingMode: SceneEnvironment.MSAA
            tonemapMode: SceneEnvironment.TonemapModeFilmic
            backgroundMode: SceneEnvironment.SkyBox
            lightProbe: Texture {
                source: "images/skybox/grass.png"
            }
        }
    }
}
