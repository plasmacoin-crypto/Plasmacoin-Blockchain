package main

/*
typedef const char* cchar_t;
*/
import "C"

import (
	"bufio"
	"bytes"
	"compress/gzip"
	"io"
	"io/ioutil"
	"log"
	"os"
	"strconv"
	"strings"
	"time"
)

// Check for errors
func check(err error, line int) {
	if err != nil {
		log.Fatal(err.Error() + " on line " + strconv.Itoa(line))
	}
}

// Compress a file using gzip
//export GzipCompress
func GzipCompress(filename C.cchar_t) C.cchar_t {
	goFilename := C.GoString(filename) // Convert from a C string to a Go string

	// Open the file
	file, err := os.Open(goFilename)
	check(err, 23)

	// Read the contents of the file
	reader := bufio.NewReader(file)
	contents, err := ioutil.ReadAll(reader)
	check(err, 27)

	// Create the compressed file (.gz)
	comp, err := os.Create(goFilename + ".gz")
	check(err, 30)

	// Make a new writer
	gzwriter := gzip.NewWriter(comp)
	defer gzwriter.Close()

	// Set the header fields
	gzwriter.Name = goFilename
	gzwriter.Comment = ""
	gzwriter.ModTime = time.Now()

	// Write the compressed data to the file
	_, err = gzwriter.Write(contents)
	check(err, 42)

	return C.CString(comp.Name())
}

// Decompress a gzip-compressed file
//export GzipDecompress
func GzipDecompress(filename C.cchar_t) C.cchar_t {
	goFilename := C.GoString(filename) // Convert from a C string to a Go string

	// Open the file for reading and writing
	input, err := os.OpenFile(goFilename, os.O_RDONLY, 0)
	check(err, 55)

	defer input.Close()

	// Read the file as a byte slice
	b, err := ioutil.ReadFile(input.Name())
	check(err, 56)

	// Create a byte reader and use it to make a gzip reader
	breader := bytes.NewReader(b)
	gzreader, err := gzip.NewReader(breader)

	check(err, 62)
	defer gzreader.Close()

	// Create a destination file
	output, err := os.Create(strings.SplitAfterN(goFilename, ".gz", 1)[0])
	check(err, 71)

	// Copy the decompressed data from the gzip reader to the destination file
	if _, err = io.Copy(output, gzreader); err != nil {
		check(err, 66)
	}

	os.Remove(goFilename) // Delete the compressed data

	return C.CString(output.Name())
}

func main() {}
