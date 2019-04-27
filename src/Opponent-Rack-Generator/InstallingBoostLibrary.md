
# Installing Boost Library for Visual Studio 17:

<mark>Steps</mark>:

 - Download the Library from [Here](https://www.boost.org/users/history/version_1_69_0.html)
 - Un-Zip the library on Desktop.
 - Open the Un-Ziped Folder and Copy Boost Folder inside it.
 - Create a folder named <mark>boost</mark> inside the program files in your <mark>C</mark> Partition.
 - Paste the folder that you copied inside that folder, it should look like this: C:/Program Files/boost/boost_1_69_0
 - Open Visual Studio 17 -> The Project -> Right-click on the project and select properties.
 - Configuration Properties -> VC++ Directories -> Include Directories
 - Add this Path: C:\Program Files\boost\boost_1_69_0
 - Select Ok -> Apply.
 - <mark>Again</mark> Right-click on the project and select properties.
 - Configuration Properties -> C/C++ -> Preprocessor
 - Click on pre-compiler header.
 - Click on create/use pre-compiled header (if it is used in your version).
 - Select not using pre-compiled header.
 - Select Apply.


 #Important Note:

 - After you have finished the above steps, Open the folder where Boost is installed:  <mark>C:/Program Files/boost/boost_1_69_0</mark>

 - Go to were the extracted file was <mark>C:/Program Files/boost/boost_1_69_0</mark>
 - Click on booststrap.bat (don't bother to type on the command window just wait and don't close the window.)
 - After a while the booststrap will run and produce the same file, but now with two different names: b2, and bjam.
 - Click on b2 and wait it to run.
 - Click on bjam and wait it to run. Then a folder will be produce called stage.
 - Right click on the project -> Properties -> Linker -> General

 - Click on include additional library directory.
 - Select the part of the library <mark>C:/Program Files/boost/boost_1_69_0/stage/lib</mark>


 #It will take sometime to run so don't worry and sorry for any inconvenience installing this library may have caused.
 
 You have now installed Boost Library, enjoy ;)

 