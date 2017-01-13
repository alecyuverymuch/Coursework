
# BadgerDB quick start guide                                                   

### Building the source and documentation                                        
Before doing anything, first unzip docs.zip into the Buffer Manager folder, do not change the name of the folder.   

To build the source:  
  `$ make`

To build the real API documentation (requires Doxygen):  
  `$ make doc`

To view the documentation, open docs/index.html in your web browser after
running make doc.

### Prerequisites                                                                

If you are running this on a CSL instructional machine, these are taken care of.

Otherwise, you need:
 * a modern C++ compiler (gcc version 4.6 or higher, any recent version of clang)
 * doxygen (version 1.4 or higher)
