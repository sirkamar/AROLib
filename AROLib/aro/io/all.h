#ifndef ARO_IO_H
#define ARO_IO_H

/***************************************************************
*        Advanced References & Objects (ARO) Library           *
****************************************************************
* The Input/Output (IO) namespace includes all of the headers  *
* necessary to use the classes and functions of the AROLib     *
* related to performing input and/or output operations.        *
***************************************************************/

//#include <aro/io/Streamable.h>           // Streamable interface declaration

#include <aro/io/IOException.h>          // IOException class declaration

#include <aro/io/InputStream.h>          // InputStream class declaration
#include <aro/io/DataInputStream.h>      // DataInputStream class declaration
#include <aro/io/FileInputStream.h>      // FileInputStream class declaration
#include <aro/io/FilterInputStream.h>    // FilterInputStream class declaration
#include <aro/io/ObjectInputStream.h>    // ObjectInputStream class declaration
#include <aro/io/StringInputStream.h>    // StringInputStream class declaration
#include <aro/io/BufferedInputStream.h>  // BufferedInputStream class declaration
#include <aro/io/ByteArrayInputStream.h> // ByteArrayInputStream class declaration

#include <aro/io/PrintStream.h>          // PrintStream class declaration
#include <aro/io/OutputStream.h>         // OutputStream class declaration
#include <aro/io/DataOutputStream.h>     // DataOutputStream class declaration
#include <aro/io/FileOutputStream.h>     // FileOutputStream class declaration
#include <aro/io/FilterOutputStream.h>   // FilterOutputStream class declaration
#include <aro/io/ObjectOutputStream.h>   // ObjectOutputStream class declaration
#include <aro/io/StringOutputStream.h>   // StringOutputStream class declaration
#include <aro/io/BufferedOutputStream.h> // BufferedOutputStream class declaration
#include <aro/io/ByteArrayOutputStream.h>// ByteArrayOutputStream class declaration

#include <aro/io/Reader.h>               // Reader class declaration
#include <aro/io/FileReader.h>           // FileReader class declaration
#include <aro/io/FilterReader.h>         // FilterReader class declaration
#include <aro/io/StringReader.h>         // StringReader class declaration
#include <aro/io/BufferedReader.h>       // BufferedReader class declaration
#include <aro/io/InputStreamReader.h>    // InputStreamReader class declaration

#include <aro/io/Writer.h>               // Writer class declaration
#include <aro/io/FileWriter.h>           // FileWriter class declaration
#include <aro/io/PrintWriter.h>          // PrintWriter class declaration
#include <aro/io/FilterWriter.h>         // FilterWriter class declaration
#include <aro/io/StringWriter.h>         // StringWriter class declaration
#include <aro/io/BufferedWriter.h>       // BufferedWriter class declaration
#include <aro/io/OutputStreamWriter.h>   // OutputStreamWriter class declaration

#endif /* ARO_IO_H */
