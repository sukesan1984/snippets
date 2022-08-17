package main

import (
	"archive/zip"
	"bytes"
	"encoding/csv"
	"fmt"
	"io/ioutil"
	"os"
)

func before() {
	f, err := os.Create("sample.txt")
	if err != nil {
		panic(err)
	}
	f.Write([]byte("sample"))
	f.Close()
}

func main() {
	//	before()
	dumpCSV()

	// 圧縮対象ファイル取得
	file := find()

	// 圧縮ファイルデータ生成
	// この時点では、メモリ上に存在する
	b := compress(file)

	if err := save(b); err != nil {
		panic(err)
	}
}

func find() string {
	return "test.csv"
}

func dumpCSV() {
	userIDs := [][]string{
		[]string{"1"},
		[]string{"2"},
		[]string{"3"},
	}
	fmt.Println(userIDs)
	f, err := os.Create("test.csv")
	if err != nil {
		fmt.Println(err)
	}
	w := csv.NewWriter(f)
	w.WriteAll(userIDs)
}

func save(b *bytes.Buffer) error {
	zf, err := os.Create("sample.zip")
	if err != nil {
		return err
	}
	zf.Write(b.Bytes())
	zf.Close()
	return nil
}

func compress(file string) *bytes.Buffer {
	b := new(bytes.Buffer)
	w := zip.NewWriter(b)
	info, _ := os.Stat(file)

	hdr, _ := zip.FileInfoHeader(info)
	hdr.Name = file
	f, err := w.CreateHeader(hdr)
	if err != nil {
		panic(err)
	}
	body, err := ioutil.ReadFile(file)
	if err != nil {
		panic(err)
	}
	f.Write(body)
	w.Close()
	return b
}
