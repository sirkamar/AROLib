#ifndef ARO_IO_H
#define ARO_IO_H

/***************************************************************
*        Advanced References & Objects (ARO) Library           *
****************************************************************
* The Input/Output (IO) namespace includes all of the headers  *
* necessary to use the classes and functions of the AROLib     *
* related to performing input and/or output operations.        *
***************************************************************/

//#include <aro/io/Streamable.hpp>           // Streamable interface declaration

#include <aro/io/IOException.hpp>          // IOException class declaration

#include <aro/io/InputStream.hpp>          // InputStream class declaration
#include <aro/io/DataInputStream.hpp>      // DataInputStream class declaration
#include <aro/io/FileInputStream.hpp>      // FileInputStream class declaration
#include <aro/io/FilterInputStream.hpp>    // FilterInputStream class declaration
#include <aro/io/ObjectInputStream.hpp>    // ObjectInputStream class declaration
#include <aro/io/StringInputStream.hpp>    // StringInputStream class declaration
#include <aro/io/BufferedInputStream.hpp>  // BufferedInputStream class declaration
#include <aro/io/ByteArrayInputStream.hpp> // ByteArrayInputStream class declaration

#include <aro/io/PrintStream.hpp>          // PrintStream class declaration
#include <aro/io/OutputStream.hpp>         // OutputStream class declaration
#include <aro/io/DataOutputStream.hpp>     // DataOutputStream class declaration
#include <aro/io/FileOutputStream.hpp>     // FileOutputStream class declaration
#include <aro/io/FilterOutputStream.hpp>   // FilterOutputStream class declaration
#include <aro/io/ObjectOutputStream.hpp>   // ObjectOutputStream class declaration
#include <aro/io/StringOutputStream.hpp>   // StringOutputStream class declaration
#include <aro/io/BufferedOutputStream.hpp> // BufferedOutputStream class declaration
#include <aro/io/ByteArrayOutputStream.hpp>// ByteArrayOutputStream class declaration

#include <aro/io/Reader.hpp>               // Reader class declaration
#include <aro/io/FileReader.hpp>           // FileReader class declaration
#include <aro/io/FilterReader.hpp>         // FilterReader class declaration
#include <aro/io/StringReader.hpp>         // StringReader class declaration
#include <aro/io/BufferedReader.hpp>       // BufferedReader class declaration
#include <aro/io/InputStreamReader.hpp>    // InputStreamReader class declaration

#include <aro/io/Writer.hpp>               // Writer class declaration
#include <aro/io/FileWriter.hpp>           // FileWriter class declaration
#include <aro/io/PrintWriter.hpp>          // PrintWriter class declaration
#include <aro/io/FilterWriter.hpp>         // FilterWriter class declaration
#include <aro/io/StringWriter.hpp>         // StringWriter class declaration
#include <aro/io/BufferedWriter.hpp>       // BufferedWriter class declaration
#include <aro/io/OutputStreamWriter.hpp>   // OutputStreamWriter class declaration

#endif /* ARO_IO_H */
