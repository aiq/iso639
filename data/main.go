package main

import (
	_ "embed"
	"encoding/csv"
	"fmt"
	"io"
	"log"
	"os"
	"sort"
	"strings"
)

const marker = `
/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 https://www.loc.gov/standards/iso639-2/ISO-639-2_utf-8.txt
*******************************************************************************/
`

const fullFmtTmpl = `#include "iso639/cIso639.h"
%s

#define c_c_( Str ) (cChars){ .s=strlen(Str), .v=Str }

static cIso639 raw[%d] = {
	%s
};
cIso639Slice const C_Iso639Values = { .s=%d, .v=raw };
`

const bibFmtTmpl = `#include "iso639/cIso639p2.h"
%s
static cIso639p2 raw[%d] = {
	%s
};
cIso639p2Slice const C_Iso639p2BibValues = { .s=%d, .v=raw };
`

const terFmtTmpl = `#include "iso639/cIso639p2.h"
%s
static cIso639p2 raw[%d] = {
	%s
};
cIso639p2Slice const C_Iso639p2TerValues = { .s=%d, .v=raw };
`

const a2FmtTmpl = `#include "iso639/cIso639p1.h"
%s
static cIso639p1 raw[%d] = {
	%s
};
cIso639p1Slice const C_Iso639p1Values = { .s=%d, .v=raw };
`

//go:embed ISO-639-2_utf-8.txt
var csvFile string

func utf8Bom() string {
	return string([]byte{239, 187, 191})
}

type iso639 []string

func (i iso639) Bib() string {
	return i[0]
}

func (i iso639) Ter() string {
	if i[1] != "" {
		return i[1]
	}
	return i.Bib()
}

func (i iso639) Alpha2() string {
	return i[2]
}

func (i iso639) Name() string {
	return i[3]
}

func main() {
	bibValues := []string{}
	terValues := []string{}
	a2Values := []string{}
	fullKeys := []string{}
	fullValues := make(map[string]string)

	r := csv.NewReader(strings.NewReader(strings.TrimPrefix(csvFile, utf8Bom())))
	r.Comma = '|'
	for {
		record, err := r.Read()
		if err == io.EOF {
			break
		}
		if err != nil {
			log.Fatal(err)
		}
		if len(record) != 5 {
			log.Fatalf("invalid len %d for %s", len(record), strings.Join(record, "|"))
		}

		isoVal := iso639(record)

		bib := isoVal.Bib()
		bibVal := fmt.Sprintf("build_iso639p2_c_( '%c', '%c', '%c' )", bib[0], bib[1], bib[2])
		bibValues = append(bibValues, bibVal)

		ter := isoVal.Ter()
		terVal := fmt.Sprintf("build_iso639p2_c_( '%c', '%c', '%c' )", ter[0], ter[1], ter[2])
		terValues = append(terValues, terVal)

		a2 := isoVal.Alpha2()
		a2Val := "build_iso639p1_c_( '\\0', '\\0' )"
		if a2 != "" {
			a2Val = fmt.Sprintf("build_iso639p1_c_( '%c', '%c' )", a2[0], a2[1])
			a2Values = append(a2Values, a2Val)
		}

		fullKeys = append(fullKeys, isoVal.Bib())
		fullValues[isoVal.Bib()] = fmt.Sprintf("(cIso639){ .p1=%s, .p2B=%s, .p2T=%s, .name=c_c_( %q ) }", a2Val, bibVal, terVal, isoVal.Name())
	}

	if len(os.Args) == 1 {
		fmt.Println("use --full, --bib, --ter or --alpha2")
	} else if os.Args[1] == "--full" {
		sort.Strings(fullKeys)
		fulls := []string{}
		for _, k := range fullKeys {
			fulls = append(fulls, fullValues[k])
		}
		size := len(fulls)
		fmt.Printf(fullFmtTmpl, marker, size, strings.Join(fulls, ",\n   "), size)
	} else if os.Args[1] == "--bib" {
		sort.Strings(bibValues)
		size := len(bibValues)
		fmt.Printf(bibFmtTmpl, marker, size, strings.Join(bibValues, ",\n   "), size)
	} else if os.Args[1] == "--ter" {
		sort.Strings(terValues)
		size := len(terValues)
		fmt.Printf(terFmtTmpl, marker, size, strings.Join(terValues, ",\n   "), size)
	} else if os.Args[1] == "--alpha2" {
		sort.Strings(a2Values)
		size := len(a2Values)
		fmt.Printf(a2FmtTmpl, marker, size, strings.Join(a2Values, ",\n   "), size)
	} else {
		fmt.Println("use --bib, --ter or --alpha2")
	}
}
