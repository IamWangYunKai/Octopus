# Octopus

**This is a remote visualization app for robots.  This app can be run on Linux/Windows/Android.**

### Requirement

* Qt5.10
* Python3.5 (optional)

# Features

#### Receive Video from Local Area Network

* Splice UDP packages
* Count FPS and network latency
* Run
```bash
python send.py
```
![](./doc/camera.png)
* Multicast address: 233.233.233.233
* Port: 23333

### Draw Debug Message
* Install **[informer](https://github.com/IamWangYunKai/informer)**, and see [examples](https://github.com/IamWangYunKai/informer/tree/master/examples)
```bash
pip install informer
```
![](./doc/debug.png)

### Render the Dashboard to Display Robot Commands
* See [examples](https://github.com/IamWangYunKai/informer/tree/master/examples) in **[informer](https://github.com/IamWangYunKai/informer)**
![](./doc/dashboard.png)

#### OpenGL Render
* Render 3D objects (point cloud for example) in a high performance way
* See glitem.h/cpp
![](./doc/opengl.png)

#### Widget Render
* Old but traditional way to draw something
* See widgetosritem.h/cpp
![](./doc/widget.png)

#### Sensor Data Viewer
* See viewerinterface.h/cpp
![](./doc/viewer.png)

#### Parameters Visualization
* You can modify and save it on the interface, but parameters will only be loaded when calling:
```c++
ParamManager::instance()->loadParam(param_name, "Visualization String", value);
```
* Save as a local file named "param.ini"
* Press 'R' to reload all parameters from the local file
![](./doc/settings.png)

#### Android
* You can install JDK, Android SDK & NDK, Qt Android, and deploy this app on Android device
![](./doc/android.png)

# TODO
- [ ] Multi-machine clock synchronization
- [ ] Point cloud rendering
- [ ] Other demands

# License
MIT License