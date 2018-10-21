# 本地化方法
## 说明 
在此项目中，使用了Qt自身的本地化方法和GNU gettext，两者结合来完成CRYENGINE界面的本地化工作。

下面的&lt; CRYENGINE SDK &gt;指的是CRYENGINE源代码所在的位置。

欢迎大家PR本地化结果。

## Qt方法
### 本地化配置文件位置
&lt; CRYENGINE SDK &gt;/editor.ini

[Sandbox]

Language=zh_cn

其中,zh_cn表示为简体中文，同时也是&lt; CRYENGINE SDK &gt;/Editor/UI/Translations中翻译文件所在的子文件夹的名称。

### 本地化文件位置
&lt; CRYENGINE SDK &gt;/Editor/UI/Translations

### 翻译文本标记方法
使用QObject::tr("")包围需要进行本地化的字符串，只支持目标类型为QString的字符串。

### 翻译方法
1. 首先确认设置了系统环境变量QTDIR，并将其指定到了linguist.exe、lrelease.exe、lupdate.exe所在的文件夹或QT安装文件夹中的bin文件夹。
2. 在标记文本完成后，双击&lt; CRYENGINE SDK &gt;/Editor/UI/Translations/update_zh_cn.bat，收集需要翻译的词条。
3. 使用linguist.exe打开zh_cn中需要翻译的.ts文件，翻译其中的词条。
4. 翻译完成后，双击&lt; CRYENGINE SDK &gt;/Editor/UI/Translations/release_zh_cn.bat，发布词条库。

### 使用方法
切换到简体中文

将editor.ini中的Language设置为zh_cn即可。

切换回英文

将editor.ini中的Language设置为en_us即可.

### 限制
1. 无法本地化const char*类型的字符串
2. 无法本地化宏中的字符串
3. 无法收集非QObject宏声明的类中的词条

## GNU gettext方法
作为Qt本地化方案的补充使用，用来收集和本地化const char*类型、非QObject宏声明的类中的词条

### 本地化配置
系统环境变量

LANG=zh_CN.UTF-8

LANGUAGE=zh_CN.UTF-8

为了防止引擎崩溃和乱码，需要使用UTF-8编码格式。

### 本地化文件位置
&lt; CRYENGINE SDK &gt;/Editor/UI/Languages

其中包含与上述系统环境变量值同名的子文件夹，如zh_CN.UTF-8

其中.po文件为翻译文件，LC_MESSAGES子文件夹中的.mo文件为翻译完成后编译生成的文件。

### 翻译文本标记方法
使用gettext("")包围需要进行本地化的字符串，它输出的结果为const char*，适用于各种词条类型。

### 翻译方法
1. 首先确认在系统环境变量PATH，在其中增加一条路径：&lt; CRYENGINE SDK &gt;/Tools/gettext/bin。
2. 在标记文本完成后，双击&lt; CRYENGINE SDK &gt;/Editor/UI/Translations/1.update_[ModualName]].bat，为对应的模块收集需要翻译的词条。
3. 双击&lt; CRYENGINE SDK &gt;/Editor/UI/Translations/2.translate_zh_cn.bat为所有模块生成翻译文件*.po，存储到zh_CN.UTF-8子文件夹中。
4. 使用Poedit打开zh_CN.UTF-8子文件夹中需要翻译的.po文件，翻译其中的词条。
5. 翻译完成后，在菜单栏单击[编目]-[属性]，设置字符集为UTF-8，如果是其它字符集，会出现乱码。
6. 保存翻译结果，同时会在同级目录下编译生成对应的.mo文件。
4. 将编译生成的.mo文件移动到LC_MESSAGES子文件夹中。

### 使用方法
切换到简体中文

将系统环境变量设置为

LANG=zh_CN.UTF-8

LANGUAGE=zh_CN.UTF-8

切换回英文

将将系统环境变量设置为

LANG=en_US.UTF-8

LANGUAGE=en_US.UTF-8

### 限制
1. 无法本地化宏中的字符串