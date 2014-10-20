img2stl
=======

### Introduction
This class can be used to decompress the combined files which contain stl files (3d models) and images (png).

This work is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/4.0/.

### Functions

<code>class</code> **DeCompress**

The following functions are all available under the class *DeCompress*.
In the *Compress* class/library all the generating functions can be found for putting the files together. 
The Class only has one public function, *DeCompressPngStl()*, the rest of the functions are all just for internal use in the class. *DeCompressPngStl()* is also the only function that is nessecary for the use of the class in a program where it is to be embedded.


<code>int</code> **DeCompressPngStl(string pngstl)**

The function takes only one argument, *string pngstl*, which stores the location of the file to be decompressed. This path can be either absolute or relative.

**return**

success:

```
0
```

error:

```
1
```


<code>string</code> **getPngFileName(fstream* fileStream, int pngFileNameLenght, int stlFileNameLenght, uint64_t fileSize)**
Seeks in the compressed file for the png filename and returns the string. 
The function takes the filestream which is opened by *DecompressPngStl* and uses the *pngFileNameLenght*, *stlFileNameLenght* and *fileSize* from the values retrieved from the compressed file.

**example return**

```
originalImage.png
```

<code>string</code> **getStlFileName(fstream* fileStream, int stlFileNameLenght, uint64_t fileSize)**
Seeks in the compressed file for the stl filename and returns the string. 
The function takes the filestream which is opened by *DecompressPngStl* and uses the *stlFileNameLenght* and *fileSize* from the values retrieved from the compressed file.

**example return**

```
originalModel.stl
```

<code>int</code> **getStl(string stl, string compressedFile, uint32_t startpos, uint64_t fileSize)**
Takes the content of the stl which is retrieved from the compressed file by *startpos* and *fileSize* and opens two seperate filestreams to take the data from the *compressedFile* and transfers it to the *stl*, a new file which is created to store the model.
**return**

success:

```
0
```

error:

```
1
```

<code>int</code> **getPng(string png, string compressedFile, uint32_t endpos)**
Takes the content of the png which is retrieved from the compressed file by *endpos* and opens two seperate filestreams to take the data from the *compressedFile* and transfers it to the *png*, a new file which is created to store the model.


**return**

success:

```
0
```

error:

```
1
```

