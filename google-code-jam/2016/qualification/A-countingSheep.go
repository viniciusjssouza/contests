package main

import "fmt"

const MAX int = (1 << 10) - 1

func main() {
    var ncase, n uint
    fmt.Scanf("%d\n", &ncase)
    for i := uint(1); i <= ncase; i++ {
        fmt.Scanf("%d\n", &n)
        count := 0       
        var x uint = 1    
        for ; x <= 99 && count < MAX; x++ {
            var number uint = x * n;
            for number > 0 && count < MAX { 
              var digit uint = number % 10
              number /= 10
              count = count | (1 << digit)              
              Debug("d=%d n=%d\n", digit, number)
            } 
        }
        x--
        
        if count == MAX {
          fmt.Printf("Case #%d: %d\n", i, x*n)
        } else {
           fmt.Printf("Case #%d: INSOMNIA\n", i)
        }
    }    
}

const DEBUG bool = false

func Debug(msg string, arg ...interface{}) {
    if DEBUG == true {
        fmt.Printf(msg, arg...)
    }
}