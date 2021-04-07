package main

import (
	"fmt"
	"log"
	"strings"

	mail "github.com/curious-eyes/jmail"
)

func main() {
	msg := `Date: Wed, 16 Sep 2015 05:32:06 +0900
From: Gopher <from@example.com>
To: Another Gopher <to@example.com>
Subject: =?UTF-8?Q?=E7=94=9F=E6=B4=BB=E3=81=AE=E3=81=BB=E3=81=A8=E3=82=93=E3=81=A9=E3=82=92?=
 =?UTF-8?Q?=E5=9C=B0=E4=B8=AD=E3=81=A7=E9=81=8E=E3=81=94=E3=81=99?=
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: quoted-printable

=E3=83=9B=E3=83=AA=E3=83=8D=E3=82=BA=E3=83=9F=20=28=E8=8B=B1=3A=20Gopher=
=29=E3=81=AF=E3=80=81=E5=93=BA=E4=B9=B3=E7=B6=B1=E3=83=8D=E3=82=BA=E3=83=
=9F=E7=9B=AE=EF=BC=88=E9=BD=A7=E6=AD=AF=E7=9B=AE=EF=BC=89=E3=83=8D=E3=82=
=BA=E3=83=9F=E4=BA=9C=E7=9B=AE=E3=83=9B=E3=83=AA=E3=83=8D=E3=82=BA=E3=83=
=9F=E7=A7=91=E3=81=AB=E5=B1=9E=E3=81=99=E3=82=8B=E5=93=BA=E4=B9=B3=E9=A1=
=9E=E3=81=AE=E7=B7=8F=E7=A7=B0
`
	r := strings.NewReader(msg)
	m, err := mail.ReadMessage(r)
	if err != nil {
		log.Fatal(err)
	}
	header := m.Header
	fmt.Println("Date:", header.Get("Date"))
	fmt.Println("From:", header.Get("From"))
	fmt.Println("To:", header.Get("To"))

	fmt.Println("Subject:", m.DecSubject())
	body, err := m.DecBody()
	if err != nil {
		log.Fatal(err)
	}
	fmt.Printf("%s", body)
}
