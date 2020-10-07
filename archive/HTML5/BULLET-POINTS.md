1.认识HTML5——欢迎来到Web镇
	HTML5是最新版本的HTML。它引入了简化的标记、新的语义和媒体元素，另外要依赖一组支持Web应用的JavaScript库。
	XHTML不再是Web页面的标准。开发人员和W3C决定还是继续拓展和改进HTML。
	新的、更为简单的HTML5 doctype在较老的浏览器上也得到支持，这些浏览器看到这个doctype时会使用标准模式。
	<script>标记或指向CSS的样式表链接中不再需要type类型。现在JavaScript和CSS是默认类型。
	用于指定字符集的<meta>标记已经大为简化，只包含字符编码。
	UTF-8现在是Web上使用的标准字符集。
	对doctype和<meta>标记做出修改不会影响页面在老浏览器上的显示。
	HTML5新元素是HTML 4元素的一个超集，这说明，较老的页面在现代浏览器中仍能正常工作。
	按官方说法，HTML5标准在2014年前不会正式完成，不过大多数现代浏览器在此之前就能提供支持。
	HTML5引入了一些元素，可以向页面增加新的语义，与HTML 4.01相比，可以提供更多选项来创建Web页面结构。
	HTML5中的很多新特性都需要JavaScript来充分加以利用。
	通过使用JavaScript，可以与DOM交互，也就是文档对象模型（Document Object Model）。
	DOM是Web页面的浏览器内部表示。通过使用JavaScript，你可以访问元素、修改元素，还可以向DOM增加新元素。
	JavaScript API是一个“应用程序接口”。利用API，可以控制HTML5的所有方面，比如2D绘图、视频回放等等。
	JavaScript是世界上最流行的语言之一。最近几年，JavaScript实现有了显著改进。
	可以检测浏览器中是否支持某个新特性，如果不支持还能够妥善地降级。
	CSS是HTML5的样式标准，很多人用“HTML5”描述创建Web应用所用的技术家族时，都包含CSS。
//我的脑子一定是进水了，竟然会记录这~

2.介绍JavaScript和DOM——一点点代码
	使用var声明一个JavaScript变量。
	数字、布尔值和串是基本类型。
	布尔值为true和false。
	数字可以是整数或浮点数。
	未赋值的变量值为undefined。
	undefined和null是两个不同的值。undefined表示一个变量未赋值；null表示这个变量有一个空值。
	数值表达式、布尔表达式和串表达式会分别得到一个数、布尔值或串值。
	要重复执行代码块，可以使用for或while循环。
	for循环和while循环可以做同样的事情，要根据具体情况使用最合适的形式。
	要结束一个for或while循环，某个时刻 条件测试必须为false。
	可以使用if/else语句根据一个条件测试做出判断。
	条件测试是布尔表达式。
	可以向Web页面的head部分或体部分增加JavaScript，或者把它放在单独的文件中，并从Web页面链接这个文件。
	要用<script>元素包围你的JavaScript代码（或指向代码的链接）。
	浏览器加载一个Web页面时，他会创建一个文档对象模型（Document Object Model，DOM），这是Web页面的一个内部表示。
	通过使用JavaScript检查和修改DOM，可以使你的Web页面有交互性。
	可以使用document.getElementById访问页面中的一个元素。
	document.getElementById使用一个元素的id在DOM中查找元素。
	可以使用一个元素的innerHTML属性修改这个元素的内容。
	如果你想在页面完全加载之前访问或修改元素，会得到一个JavaScript错误，你的代码将不能正常工作。
	将一个函数赋至window.onload属性，可以在浏览器完成页面加载之后运行这个函数中的代码。
	可以使用一个数组来存储多个值。
	要访问一个数组中的一个值，需要使用索引。索引是一个整数，指定数组中元素的位置（从0开始）。
	数组的length属性会告诉你数组中有多少个元素。
	通过结合循环和数组，可以按顺序访问一个数组中的各个元素。
	Math是一个JavaScript库，包含大量与数学相关的函数。
	Math.random会返回一个介于0和1的浮点数（但是不会为1）.
	Math.floor把一个浮点数小数点后面的所有位去除，将它转换为一个整数。

3.事件与处理程序——一点点交互
	你的浏览器中一直在发生很多事件。如果你想对这些事件做出相应，就要用事件处理程序来处理这些事件。
	点击Web页面上的一个按钮是会触发按钮点击事件。
	处理一个按钮点击事件时，要注册一个函数来处理这个事件。要做到这一点，需要编写一个函数，并把按钮的onclick属性设置为这个函数名。
	如果注册了一个按钮点击事件处理程序，点击这个按钮时就会调用这个函数。
	要编写函数代码作为处理程序对按钮点击事件做出相应。可以提醒用户或者更新页面，也可以做其它相应。
	要得到用户在一个表单输入文本域中输入的文本，要使用这个输入域的value属性。
	如果用户没有向表单输入文本域输入任何内容，这个域的值将是空串（""）。
	可以用一个if测试和==来比较变量和空串是否相等。
	要把一个新元素增加到DOM，首先需要创建这个元素，然后增加这个元素作为某个元素的子元素。
	使用document.createElement可以创建一个新元素。将标记名（例如，"li"）传入函数调用，指示要创建的元素。
	要在DOM中增加一个元素作为某个父元素的子元素，需要得到这个父元素的引用，并对父元素调用appendChild，传入要增加的子元素。
	如果使用appendChild向一个父元素增加多个子元素，每个新的子元素会追加到其他子元素的后面，所以他们会出现在页面中其他子元素的后面或下面（假设没有用CSS改变页面布局）。
	可以使用Web存储API（localStorage）在用户的浏览器中存储数据。
	我们使用localStorage保存播放列表中的歌曲，这里采用了成品代码。你会在第九章了解更多有关localStorage的内容。
	下一张你更多地了解DOM和JavaScript特性，比如函数和对象。

4.JavaScript和对象——正式JavaScript
	要创建一个函数，要使用function关键字，如果有参数，还要加上小括号来包含参数。（个人见解：没有形参也要加小括号）
	函数可以是命名函数，也可以以是匿名的。
	函数的命名规则与变量命名规则相同。
	函数体放在大括号之间，包含完成函数工作的具体语句。
	函数可以用return语句返回一个值。
	要调用一个函数，需要使用函数名，并传入它需要的所有实参。
	JavaScript使用传值方式传递参数。
	传递一个对象作为一个函数的实参时，比如dog，形参会得到这个对象引用的一个副本。
	函数中定义的变量，包括形参，都称为局部变量。
	函数外定义的变量称为全局变量。
	局部变量在定义该变量的函数之外不可见，这称为变量的作用域。
	如果声明一个局部变量时与一个全局变量同名，这个局部变量会遮蔽全局变量。
	从页面链接到多个JavaScript文件时，所有全局变量都定义在同一个全局空间中。
	如果赋一个新变量而没有使用var关键字，这个变量就是全局的，即使是在一个函数中首次赋值。
	函数也是值，可以赋给变量、传递给其他函数、存储在数组中，还可以赋给对象属性。
	对象是属性的集合。
	可以使用点记法或[]记法访问对象的属性。
	如果使用[]记法，要把属性名作为一个串用括号引起来，例如myoBJECT["name"].
	可以改变一个属性的值、删除属性，或者向对象增加新属性。
	可以使用一个for-in循环枚举对象的属性。
	赋给一个对象属性的函数称为方法。
	方法可以使用一个特殊的关键字this来引用调用这个方法的对象。
	构造函数是创建对象的函数。
	构造函数的任务是创建一个新对象，并初始化这个对象的属性。
	要调用一个构造函数创建对象，需要使用new关键字。例如new Dog()。
	这本书中一直在使用对象，包括document、window和很多元素对象。
	window是全局对象。
	document对象是window的一个属性
	document.getElementById方法会返回一个元素对象。

5.实现HTML位置感知——地理定位
	地理定位并不“正式”算是HTML5规范的一部分，不过可以认为它属于HTML5规范“家族”。
	有很多方法来确定你的位置，这取决于你的设备。
	与蜂窝基站三角定位或网络IP相比，GPS是获得位置的一种更为精确的方法。
	没有GPS的移动设备可以使用蜂窝基站三角定位来确定位置。
	地理定位API有三个方法和一些属性。
	地理定位API中的主要方法是getCurrentPosition，这是navigator.geolocation对象的一个方法。
	getCurrentPosition有一个必要参数，即成功处理程序，还有两个可选的参数，分别是错误处理程序和选项。
	position对象传递到成功处理程序，其中包含位置的信息，包括经度和纬度。
	position对象包含coords属性，这是一个coordinates对象。
	coordinates对象的属性包括纬度(latitude)、经度(longitude)和精度(accuracy)。
	有些设备可能还支持其他coordinates属性：高度(altitude)、高度精度(altitudeAccuracy)、朝向(heading)和速度(speed)。
	使用accuracy属性来确定位置的精确度(单位千米)。
	调用getCurrentPosition时，浏览器必须验证你允许共享你的位置。
	watchPosition是geolocation对象的一个方法，会监视你的位置，并在位置改变时调用一个成功处理程序。
	类似于getCurrentPosition，watchPosition有一个必要参数，即成功处理程序，还有两个可选参数，分别是错误处理程序和选项。
	使用clearWatch停止监视位置。
	使用watchPosition时，设备需要更多能量，所以可能会缩短你的电池寿命。
	getCurrentPosition和watchPosition的第三个参数options对象有一些属性，可以设置这些属性来控制地理定位API的行为。
	maximumAge属性确定getCurrentPosition是否使用一个缓存位置，如果是，它指定了请求一个全新位置前这个位置的最大年龄。
	timeout属性确定调用错误处理程序之前getCurrentPosition可以有多长时间来得到一个全新的位置。
	enableHighAccuracy属性向设备提供一个提示，如果可以得到一个高精度的位置，需要更多能量。
	可以使用地理定位API并结合Google Maps API在地图上显示你的位置。

7 秀出你的艺术天分——画布
	画布是一个元素，可以放在页面上来创建一个绘制空间。
	除非你指定，否则画布没有默认的样式或内容（所以在画布上绘制内容或用CSS增加边框之前，在页面上是看不到画布的）。
	页面上可以有多个画布。当然，需要为每个画布提供一个唯一的id，以便使用JavaScript分别访问。
	要指定画布元素的大小，可以使用元素的width和height属性。
	画布上所有的内容都使用JavaScript绘制。
	要在画布上绘制，首先需要创建一个上下文。目前，2D上下文是唯一的选择，不过将来可能还会有其他上下文类型。
	要在画布上绘制，首先需要有一个上下文。因为上下文提供了一个特定的接口（例如，2D或3D）。你可以从多种接口中选择来完成画布上的绘制。
	使用上下文属性和方法来访问画布。
	要在画布中绘制一个矩形，可以使用csontex.fillRect方法。这个方法会创建一个矩形，并填充指定的颜色。
	要创建一个矩形轮廓，可以使用strokeRect而不是fillRect。
	使用fillStyle和strokeStyle可以改变默认的填充和笔划颜色，默认颜色为黑色。
	可以使用CSS中同样的的格式指定颜色（例如，"black"、"#000000"、"rgb(0, 0, 0)"。记住要在fillStyle两边加上引号。
	并没有一个fillCircle方法。要在画布上绘制一个圆，需要绘制一个弧。
	要创建任意的形状或弧，首先要创建一个路径。
	路径是一个不可见的线或形状，它定义了画布上的一条线或区域。用笔画描出路径或填充路径之前，路径是看不到的。
	要创建一个三角形，可以使用beginPath创建一个路径，然后用moveTo和lineTo来 绘制路径。使用closePath可以连接路径上的两个点。
	要绘制一个圆，可以创建一个360°的弧。起始角为0，终止角为360°。
	画布中使用弧度来指定角，而不是使用度，所以需要从度转换为弧度来指定起始角和终止角。
	360° = 2PI弧度。
	要在画布上绘制文本，可以使用fillText方法。
	在画布中绘制文本时，需要使用上下文属性指定位置、样式和其他属性。
	设置一个上下文属性时，他会应用到后面的所有绘制操作，直到你再次改变这个属性。例如，改变fillStyle会影响设置fillStyle知乎绘制的所有形状和文本的颜色。
	可以用drawInage方法向画布增加图像。
	要增加一个图像，首先需要创建一个图象对象，并确保它完全加载。
	在画布上绘制就像在图形程序中完成“位图”绘制。

9 在本地存储
	Web存储是浏览器中的一个存储库，也是一个API，可以用来从这个本地存储库保存和获取数据项。
	大多数浏览器都为每个源提供了至少5MB的存储空间。
	Web存储包括本地存储和会话存储。
	本地存储是持久的，即使你关闭浏览器窗口或退出浏览器，本地存储仍然保留。
	会话存储中的数据项会在你关闭浏览器窗口或退出浏览器时删除。会话存储很适合临时数据项，而不是长期存储。
	本地存储和会话存储使用完全相同的API。
	Web存储按源（可以认为是域）来组织。源就是Web上文档的位置（例如，wickedlysmart.com或headfirstlabs.com）。
	每个域有一个单独的存储空间，所以存储在一个源的数据项对另一个源中的Web页面是不可见的。
	使用localStorage.setItem(key)可以从本地存储获取一个值。
	可以使用与关联数组相同的语法在本地存储中设置和获取数据项。可以使用localStorage中的键。
	localStorage.length是一个给定源localStorage中的数据项数。
	使用浏览器中的控制台可以查看和删除localStorage中的数据项。
	可以从localStorage直接删除数据项，只需右键点击一个数据项，并选择delete（注意，并非所有浏览器中都奏效）。
	可以在代码中使用removeItem(key)的方法和clear方法删除localStorage中的数据项。注意，clear方法会删除你完成这个清空操作时源源所在localStorage中的所有内容。
	每个localStorage中的数据项的键必须是唯一的。如果使用与一个现有数据项相同的键，会覆盖这个数据项的值。
	要生成一个唯一的键，一种方法是使用当前时间（自1970年以来的毫秒数），并使用Date对象的getTime()方法。
	要为你的Web应用创建一个合适的命名机制，使得即时数据项从本地存储删除，或者如果另一个应用在本地存储中创建了数据项，也能正常工作。
	Web存储目前只支持存储字符串作为对应键的值。
	可以使用parseInt或者praseFloat将localStorage中作为字符串的数字转换回真正的数字。
	如果需要存储更复杂的数据，可以使用JavaScript对象，在存储之前会使用JSON.stringify把他们转换为字符串，在获取之后会使用JSON.parse再将其转换回对象。
	本地存储对于移动设备尤其有用，可以用来降低宽带需求。
	会话存储类似于本地存储，只不过浏览器存储库中保存的内容不会持久存储，如果你关闭标签页、窗口或退出浏览器，他们就不复存在。会话存储对于短期存储很有用，如购物会话。