package main

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
func GzipCompress(filename string) *os.File {
	// Open the file
	file, err := os.Open(filename)
	check(err, 23)

	// Read the contents of the file
	reader := bufio.NewReader(file)
	contents, err := ioutil.ReadAll(reader)
	check(err, 27)

	// Create the compressed file (.gz)
	comp, err := os.Create(filename + ".gz")
	check(err, 30)

	// Make a new writer
	gzwriter := gzip.NewWriter(comp)
	defer gzwriter.Close()

	// Set the header fields
	gzwriter.Name = filename
	gzwriter.Comment = ""
	gzwriter.ModTime = time.Now()

	// Write the compressed data to the file
	_, err = gzwriter.Write(contents)
	check(err, 42)

	return comp
}

// Decompress a gzip-compressed file
func GzipDecompress(file *os.File) *os.File {
	// Open the file for reading and writing
	input, err := os.OpenFile(file.Name(), os.O_RDONLY, 0)
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
	output, err := os.Create(strings.SplitAfterN(file.Name(), ".gz", 1)[0])
	check(err, 71)

	// Copy the decompressed data from the gzip reader to the destination file
	if _, err = io.Copy(output, gzreader); err != nil {
		check(err, 66)
	}

	os.Remove(file.Name()) // Delete the compressed data

	return output
}
