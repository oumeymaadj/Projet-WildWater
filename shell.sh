#!/bin/bash



# aff dure totale en ms
duree_totale() {
    fin_tps=$(date +%s) 
    r_duree=$((fin_tps - START_TIME))
    echo "La durée totale est : $((r_duree * 1000)) mili-seconde"
}

#aff une erreur et arrete le script
fct_error() {
    echo "Erreur : $1" >&2
    duree_totale
    exit 1
}


# récupére les arguments ecrit dans le terminal
recup_arg() {
    if [ $# -lt 2 ]; then
        fct_error "Reesayer manque d'arguments"
    fi

    fichier_d="$1" #chemin du fichier
    Type="$2"      #histo ou leaks
    Option="$3"    #max src real id usine
    NB_ARG=$#      #nb argument
}


# vérif la validité des arguments
arg_valid_T() {
    case "$Type" in

        leaks)
            if [ "$NB_ARG" -ne 3 ]; then # le prog shell ne verifie pas si l' id existe ou pas !
                fct_error "Nombre d'arguments insuffisant pour leaks !"
            fi
            ;;
              
        histo)
            if [ "$NB_ARG" -ne 3 ]; then
                fct_error "Nombre d'arguments insuffisant pour histo !"
            fi

            if [ "$Option" != "src" ] && [ "$Option" != "max" ] && [ "$Option" != "all" ] && [ "$Option" != "real" ]; then
                fct_error "Option invalide choissir entre | max ; src ; real ; all |"
            fi
            ;;
            
        *)
            fct_error "Erreur, Choix possible : | histo OU leaks |"
            ;;
    esac
}


fct_compilation() {

    if [ ! -x "./wildwater" ]; then
        echo "Compilation..."
        make
        if [ $? -ne 0 ]; then
            fct_error "Mince, echec lors de la compilation"
        fi
    fi

}

# vérif l'existence/ lecture fichier
verif_fichier() {
    if [ ! -f "$fichier_d" ]; then # si ! fichier
        fct_error "Fichier introuvable :("
    fi

    if [ ! -r "$fichier_d" ]; then # si ! permission de le lire
        fct_error "Fichier non lisible"
    fi
}

crea_histo() {
    Fichier_sortie="histo_${Option}.dat"

    ./wildwater "$fichier_d" histo "$Option" 
    if [ $? -ne 0 ]; then
        fct_error "Oups, erreur lors de la generation de l'histo"
    fi

    echo "Histogramme genere : $Fichier_sortie"
}

# lance calcul de fuite
crea_leaks() {
    Fichier_sortie="leaks.dat"

    ./wildwater "$fichier_d" leaks "$Option" 
    if [ $? -ne 0 ]; then
        fct_error "Oups, erreur lors du traitement de leaks"
    fi

    echo "Fichier leaks généré : $Fichier_sortie"
}




generation_image() {
    Fichier_data="histo_${Option}.dat"

    if [ ! -f "$Fichier_data" ]; then
        fct_error "Fichier pour la generation d'image introuvable : $Fichier_data"
    fi

  gnuplot << EOF
set terminal png size 900,600
set datafile separator ";"
set grid
set xtics rotate by -45
set style fill solid 0.8 border -1
set boxwidth 0.7
set style line 1 lc rgb "#1f77b4"

# 50 plus petites usines
set output "${Fichier_data%.dat}_50_small.png"
set title "50 plus petites usines (${Option})"
set xlabel "Usines"
set ylabel "Volume (M.m3)"
plot "< tail -n +2 $Fichier_data | sort -t';' -k2,2n | head -n 50" \
     using 2:xtic(1) with boxes ls 1 notitle

# 10 plus grandes usines
set output "${Fichier_data%.dat}_10_large.png"
set title "10 plus grandes usines (${Option})"
set xlabel "Usines"
set ylabel "Volume (M.m3)"
plot "< tail -n +2 $Fichier_data | sort -t';' -k2,2nr | head -n 10" \
     using 2:xtic(1) with boxes ls 1 notitle
EOF


    if [ $? -ne 0 ]; then
        fct_error "Erreur lors de la generation des images"
    fi

    echo "Images genere à partir de $Fichier_data"
}


#fonction qui genere l'histogramme pour l'argument "all"
generation_image_all() {

    Fichier_data="histo_all.dat"

    if [ ! -f "$Fichier_data" ]; then
        fct_error "Fichier histo_all.dat introuvable"
    fi

    gnuplot << EOF
set terminal png size 1100,600
set datafile separator ";"

# histogramme empilé
set style data histograms
set style histogram rowstacked
set style fill solid 0.65 border -1     # plus transparent
set boxwidth 0.8

set grid ytics
set xtics rotate by -45

# couleurs 
set style line 1 lc rgb "#8FBCE6"   # bleu pastel : volume reel
set style line 2 lc rgb "#F4A6A6"   # rouge pastel : pertes
set style line 3 lc rgb "#9ED9A1"   # vert pastel : marge restante

unset key     #supprimer la legende
set output "histo_all_50_small.png"
set title "Histogramme cumule des 50 plus petites usines"
set xlabel "Usines"
set ylabel "Volume (M.m3)"

plot "< tail -n +2 $Fichier_data | sort -t';' -k2,2n | head -n 50" \
    using 4:xtic(1) notitle ls 1, \
    '' using (\$3-\$4) notitle ls 2, \
    '' using (\$2-\$3) notitle ls 3


set key top right    #on remet la legende pour les 10 plus grandes
set output "histo_all_10_large.png"
set title "Histogramme cumule des 10 plus grandes usines"
set xlabel "Usines"
set ylabel "Volume (M.m3)"

plot "< tail -n +2 $Fichier_data | sort -t';' -k2,2nr | head -n 10" \
     using 4:xtic(1) title "Volume reel" ls 1, \
     '' using (\$3-\$4) title "Pertes apres captage" ls 2, \
     '' using (\$2-\$3) title "Marge restante" ls 3
EOF

    if [ $? -ne 0 ]; then
        fct_error "Erreur lors de la generation de l'histogramme all"
    fi

    echo "Histogrammes cumulés générés :"
    
}


START_TIME=$(date +%s)

recup_arg "$@"
arg_valid_T
verif_fichier
fct_compilation

case "$Type" in
    histo)
        crea_histo
        if [ "$Option" = "all" ]; then
            generation_image_all
        else
            generation_image
        fi
        ;;
    leaks)
        crea_leaks
        ;;
esac

duree_totale
exit 0
