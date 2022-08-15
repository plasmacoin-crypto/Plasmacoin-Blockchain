//
// FILENAME: compression.go | Plasmacoin Cryptocurrency
// DESCRIPTION: Compress and decompress files uisng gzip
// CREATED: 2021-09-11 @ 3:42 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

package netutils

import (
	"bufio"
	"bytes"
	"compress/gzip"
	"io"
	"os"
	"strings"
	"time"
)

// Compress a file using gzip
//
//export GzipCompress
func GzipCompress(filename string) string {
	// Open the file
	file, err := os.Open(filename)
	Check(err, 26)

	// Read the contents of the file
	reader := bufio.NewReader(file)
	contents, err := io.ReadAll(reader)
	Check(err, 31)

	// Create the compressed file (.gz)
	comp, err := os.Create(filename + ".gz")
	Check(err, 35)

	// Make a new writer
	gzwriter := gzip.NewWriter(comp)
	defer gzwriter.Close()

	// Set the header fields
	gzwriter.Name = filename
	gzwriter.Comment = ""
	gzwriter.ModTime = time.Now()

	// Write the compressed data to the file
	_, err = gzwriter.Write(contents)
	Check(err, 48)

	return comp.Name()
}

// Decompress a gzip-compressed file
//
//export GzipDecompress
func GzipDecompress(filename string) string {
	// Open the file for reading and writing
	input, err := os.OpenFile(filename, os.O_RDONLY, 0)
	Check(err, 60)

	defer input.Close()

	// Read the file as a byte slice
	b, err := os.ReadFile(input.Name())
	Check(err, 66)

	// Create a byte reader and use it to make a gzip reader
	breader := bytes.NewReader(b)
	gzreader, err := gzip.NewReader(breader)

	Check(err, 72)
	defer gzreader.Close()

	// Create a destination file
	output, err := os.Create(strings.SplitAfterN(filename, ".gz", 1)[0])
	Check(err, 77)

	// Copy the decompressed data from the gzip reader to the destination file
	if _, err = io.Copy(output, gzreader); err != nil {
		Check(err, 81)
	}

	os.Remove(filename) // Delete the compressed data

	return output.Name()
}
