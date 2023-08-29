package main

import (
	"fmt"

	"github.com/ericlagergren/decimal"
	"github.com/volatiletech/sqlboiler/types"
	"go.mercari.io/go-bps/bps"
)

func main() {
	rate := bps.NewFromPercentage(85)
	fmt.Println(rate.Mul(100).Amounts())
	fmt.Println(rate.Mul(100).Rat().Float64())
	rate2, err := bps.NewFromString(".05")
	if err != nil {
		panic(err)
	}
	fmt.Println(rate2.Mul(123).Amounts())
	fmt.Println(rate2.Mul(123).Rat().Float64())

	decimalRate := types.NewDecimal(decimal.New(1, 2))
	rate3, err := bps.NewFromString(decimalRate.String())
	if err != nil {
		panic(err)
	}
	fmt.Println(rate3.Mul(1001).Amounts())
}
