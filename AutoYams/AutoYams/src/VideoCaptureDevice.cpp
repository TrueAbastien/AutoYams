#include <AutoYams\opencv\VideoCaptureDevice.h>

VideoCaptureDevice::VideoCaptureDevice(int _id, QString _name, QString _path)
	: ID(_id), deviceName(_name), devicePath(_path)
{
	const int size = _name.length();
	if (size >= 3)
	{
		deviceAlias = _name.left(3) + QString::number(size) + _name.right(3);
		deviceAlias.replace(' ', '_');
	}
	else deviceAlias = "none";
}

void VideoCaptureDevice::get(QList<std::shared_ptr<VideoCaptureDevice>>& content)
{
	content.clear();
	DeviceEnumerator de;
	auto map = de.getVideoDevicesMap();

	foreach(auto ele, map)
		content.append(std::make_shared<VideoCaptureDevice>(ele.first, ele.second.deviceName.data(), ele.second.devicePath.data()));
}
