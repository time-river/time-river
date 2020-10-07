/*
	遗憾，没照抄成功
	navigator
		.geolocation
		若不支持地理定位，navigator.geolocation返回null
			.getCurrentPosition(successHandler, errorHandler, positionOptions)		
				successHandler是一个函数，如果浏览器能成功地确定你的地理位置就会调用这个函数
				  成功处理程序（或回调）会在确定位置时调用，并传入一个position对象
					position
						.coords	
							.latitude 
							.longitude 
							.accuracy 
							.altitude 
							.altitudeAccuracy 
							.heading 
							.speed
						.timestamp 包含创建这个对象的时间
				errorHandler是另外一个函数，如果出了问题，浏览器无法确定位置，则会调用这个函数
				  var errorTypes = {
					0: "Unknown error",
					1: "Permission denied",
					2: "Position is not available",
					3: "Request timeout"
				  };
				options参数允许定制地理定位的方法
				  var options = {
					enableHighAccuracy: true, //启用高精度
					timeout: Infinity, //确定用户的位置要多久
					maximumAge: 60000， //调整计算机多久重新计算或确定位置,缺省值Infinity
						maximumAge：600000 如果浏览器有一个年龄小于10分钟的缓存位置，则会使用这个位置；否则请求全新位置
						timeout:1000, maximumAge: 600000 如果浏览器有一个年龄小于10分钟的缓存位置，则会使用这个位置；否则请求全新位置，不过前提是在1s内得到
						timeout:0, maximumAge:Infinity 使用缓存位置，若没有缓存位置，则请求全新位置
						timeout:Infinity, maximumAge:0 使用全新位置
				errorHandler和options参数是可选的
			.watchPosition(successHandler, errorHandler, positionOptions)	
				函数如何工作
					1.应用调用watchPosition，传入一个成功处理函数
					2.watchPosition在后台不断监视着位置
					3.位置改变时，watchPosition调用成功处理函数来报告新位置
					4.watchPosition继续监视位置（并向成功处理程序报告），直至调用clearWatch将它清除
			.clearWatch()
/* myLoc.js */

var watchId = null;
var map = null;
var ourCoords =  {
	latitude: 47.624851,
	longitude: -122.52099
};
var prevCoords = null;

window.onload = getMyLocation;

function getMyLocation() {
	if (navigator.geolocation) {
		var watchButton = document.getElementById("watch");
		watchButton.onclick = watchLocation;
		var clearWatchButton = document.getElementById("clearWatch");
		clearWatchButton.onclick = clearWatch;
	}
	else {
		alert("Oops, no geolocation support");
	}
}

function displayLocation(position) {
	var latitude = position.coords.latitude;
	var longitude = position.coords.longitude;

	var div = document.getElementById("location");
	div.innerHTML = "You are at Latitude: " + latitude + ", Longitude: " + longitude;
	div.innerHTML += " (with " + position.coords.accuracy + " meters accuracy)";

	var km = computeDistance(position.coords, ourCoords);
	var distance = document.getElementById("distance");
	distance.innerHTML = "You are " + km + " km from the WickedlySmart HQ";

	if (map == null) {
		showMap(position.coords);
		prevCoords = position.coords;
	}
	else {
		var meters = computeDistance(position.coords, prevCoords) * 1000;
		if (meters > 20) { //防止显示过多标记，调用scrollMapToPosition之前检查距离是否大于20m
			scrollMapToPosition(position.coords);
			prevCoords = position.coords;
		}
	}
}


// --------------------- Ready Bake ------------------
//
// Uses the Spherical Law of Cosines to find the distance
// between two lat/long points
//
function computeDistance(startCoords, destCoords) {
	var startLatRads = degreesToRadians(startCoords.latitude);
	var startLongRads = degreesToRadians(startCoords.longitude);
	var destLatRads = degreesToRadians(destCoords.latitude);
	var destLongRads = degreesToRadians(destCoords.longitude);

	var Radius = 6371; // radius of the Earth in km
	var distance = Math.acos(Math.sin(startLatRads) * Math.sin(destLatRads) + 
					Math.cos(startLatRads) * Math.cos(destLatRads) *
					Math.cos(startLongRads - destLongRads)) * Radius;

	return distance;
}

function degreesToRadians(degrees) {
	radians = (degrees * Math.PI)/180;
	return radians;
}

// ------------------ End Ready Bake -----------------

function showMap(coords) {
	var googleLatAndLong = new google.maps.LatLng(coords.latitude, 
												  coords.longitude); //构造函数，取精度和纬度，返回一个新对象，其中同时包含精度和纬度
	var mapOptions = { //设置这些选项来控制如何创建地图
		zoom: 10, //初始地图的放大或缩小程度。zoom选项指定0~21的一个值。10大约对应城市规模
		center: googleLatAndLong,  //地图在哪里居中
		mapTypeId: google.maps.MapTypeId.ROADMAP //地图的类型。  还有SATELLITE和HYBRID值可选
	};
	var mapDiv = document.getElementById("map"); //从DOM获取map<div>，把它和mapOptions传递到Map构造函数，创建google.maps.Map对象。会在页面上显示地图
	map = new google.maps.Map(mapDiv, mapOptions);  //取一个元素和选项，创建并返回一局变量map

	// add the user marker
	var title = "Your Location";
	var content = "You are here: " + coords.latitude + ", " + coords.longitude;
	addMarker(map, googleLatAndLong, title, content);
}

function addMarker(map, latlong, title, content) { //addMarker函数取一个地图、一个Google样式的纬度和经度，标记的标题，以及信息窗口的一些内容
	var markerOptions = {
		position: latlong,
		map: map,
		title: title,
		clickable: true //希望点击这个大头钉时能够显示一个信息窗口
	};
	var marker = new google.maps.Marker(markerOptions);//使用Google API提供的另一个构造函数创建marker对象，并传入创建的markerOptions对象

	var infoWindowOptions = {  //为窗口信息定义一些选项
		content: content, //内容
		position: latlong //经度和纬度
	};

	var infoWindow = new google.maps.InfoWindow(infoWindowOptions); //创建信息窗口

	google.maps.event.addListener(marker, 'click', function() { //用Google Maps addListener方法为点击事件增加一个“监听者”，向监听者传入一个函数，用户点击标记时就会调用一个函数
		infoWindow.open(map); //点击标记时，会调用这个函数，在地图上打开信息窗口
	});
}


function displayError(error) {
	var errorTypes = {
		0: "Unknown error",
		1: "Permission denied",
		2: "Position is not available",
		3: "Request timeout"
	};
	var errorMessage = errorTypes[error.code];
	if (error.code == 0 || error.code == 2) {
		errorMessage = errorMessage + " " + error.message;
	}
	var div = document.getElementById("location");
	div.innerHTML = errorMessage;
}

//
// Code to watch the user's location
//
function watchLocation() {
	watchId = navigator.geolocation.watchPosition(
					displayLocation, 
					displayError);
}

function scrollMapToPosition(coords) {
	var latitude = coords.latitude;
	var longitude = coords.longitude;

	var latlong = new google.maps.LatLng(latitude, longitude);
	map.panTo(latlong); //地图的panTo方法取这个LatLng对象并滚动地图，使新位置位于地铁中心

	// add the new marker
	addMarker(map, latlong, "Your new location", "You moved to: " + 
								latitude + ", " + longitude);
}

function clearWatch() {
	if (watchId) {
		navigator.geolocation.clearWatch(watchId);
		watchId = null;
	}
}


