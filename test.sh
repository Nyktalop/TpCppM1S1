if [ ! -f "TpCppM1S1" ]; then
    sh build.sh
fi

testfic():
{
    echo -e "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\tTesting with \"$1\" :"
    echo -e "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    cat "$1"
    echo -e "\n##################################################\n\tResults :"
    echo -e "##################################################"
    ./TpCppM1S1 < "$1"
    echo
}

if [ "$#" -eq 1 ]
    for i in Tests/*
    do
       testfic "$i"
    done
else
    testfic "Tests/$1*.tst"
fi

