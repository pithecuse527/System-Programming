
title_file="title.cdb"
track_file="track.cdb"

temp_file=/tmp/tadb.$$
temp1_file=/tmp/tbdb.$$
temp2_file=/tmp/tcdb.$$
temp3_file=/tmp/tddb.$$
temp4_file=/tmp/tedb.$$
temp5_file=/tmp/tfdb.$$

trap 'rm -f temp_file=/tmp/tadb.$$ ' EXIT
trap 'rm -f temp1_file=/tmp/tbdb.$$' EXIT
trap 'rm -f temp2_file=/tmp/tcdb.$$' EXIT
trap 'rm -f temp3_file=/tmp/tddb.$$' EXIT
trap 'rm -f temp4_file=/tmp/tedb.$$' EXIT
trap 'rm -f temp5_file=/tmp/tfdb.$$' EXIT


insert_title()                # Insert title to title DB.
{
    echo $* >> $title_file
    return
}

insert_track()                # Insert CD's track to track DB.
{
    echo $* >> $track_file
    return
}

to_return()
{
    echo -e "Any button to return \c"
    read re
    return 0
}

#############Check and make valid value part#############finish

get_confirm()                 # get confirm from user. if this func. returns 0, then proceed the add task.
{
    echo -e "Are you sure? (y/n) \c"
    while (true); do
        read x
        case "$x" in
            y | yes | Y | Yes | YES ) return 0;;
            n | no | N | No | NO )    echo
                                      echo "Cancelled"
                                      return 1;;
            *) echo "Please enter yes or no" ;;
        esac
    done
}

valid_cdcatnum_val()
{
        while (true); do #Check $cdcatnum is valid. (No special char.)
        local cdcatnum=""
			echo -e "if you want to quit q\n"
            if [ -z "$1" ]; then
                echo -e "Enter CD number : \c"    
            else                                #mode 2
                echo -e "Select the number of file want to delete : \c"    #delete mode.
            fi
            
            read cdcatnum
			if [ "$cdcatnum" != "q" ]; then
				cdcatnum_chk=${cdcatnum//[0-9]/}
           		if [ ! -z "$cdcatnum_chk" ]; then
              		echo "Please type only number."
              		continue
            	else
                	return "$cdcatnum"
           		fi
			else
				chk_confirm=1
				return
			fi
        done
}

valid_cdttitle_val()    
{     
    local cdcatnum=$1
    local cdtitle=$2
    local cdtrack=$3
    local cdttitle=""
    while [ "$cdttitle" != "q" ]
	do
		echo -e "Track $cdtrack, track title : \c"
		read cdttitle
        cdttitle_chk=${cdttitle//[A-Z,a-z,0-9]/}
        if [ ! -z "$cdttitle_chk" ]; then
            echo "Please type only number & alphabet."
            continue
        fi
		if [ -n "$cdttitle" ] ; then                #if cdttitle is not null,
			if [ "$cdttitle" != "q" ]; then         #if cdttitle is not "q",
			    insert_track "No."$cdcatnum,$cdtitle,$cdtrack,$cdttitle
		    fi
		else
			cdtrack=$((cdtrack-1))
		fi
		cdtrack=$((cdtrack+1))
	done
}

valid_cdtitlle_val()
{
    echo -e "Hi!"
    while (true); do                          #if there is no title name that user's wants, do the task.
        echo -e "Title : \c"
        read cdtitle
        cdtitle_chk=${cdtitle//[A-Z,a-z]/}
        if [ ! -z "$cdtitle_chk" ]; then
            echo "Please type only alphabet."
            continue
        fi
        if [ "$(grep "$cdtitle" $title_file | wc -l)" == "0" ]; then
            break
        fi
        echo "Already used title name! Please change it."
    done
    
}

valid_extract()            #check whether there is a valid extract
{
    if [ -z "$1" -o -z "$2" -o -z "$3" -o -z "$4" ]; then
        echo "Could not extract catalog field form $temp_file"
        return 0
    fi
    return 1
}

#############add part#############finish

add_cd()                    #take valid cdcatnum value from user and then, take title, genre, artist from user.
{
    local cdcatnum=""
    local cdtitle=""
    local cdtype=""
    local cdartist=""
    clear
    echo "----Add CD Menu----"
    
    echo -e "\n=====Current CD titles=====\n"
    echo "CD num | title | Genre | Artist "
	cut -d "," -f1 $title_file > $temp1_file
	cut -d "," -f2 $title_file > $temp2_file
	cut -d "," -f3 $title_file > $temp3_file
	cut -d "," -f4 $title_file > $temp4_file
	paste $temp1_file  $temp2_file $temp3_file $temp4_file
    echo -e "\n===========================\n"
    
	chk_confirm=0
    valid_cdcatnum_val    # make valid $cdcatnum
    cdcatnum=$?
    if [ "$chk_confirm" == "0" ]; then
    	if [ "$(grep "^No.$cdcatnum\>" $title_file | wc -l)" == "0" ]; then        
	    	while (true); do                                                
            	echo -e "Title : \c"
            	read cdtitle
            	if [ "$(grep "$cdtitle" $title_file | wc -l)" == "0" ]; then
                    break
                fi
                    echo "Already used title name! Please change it."
                done
	    	echo -e "Genre : \c"
	    	read cdtype

	    	echo -e "Artist : \c"
	    	read cdartist
		else
	    	echo "Same CD exists."
	    	to_return
	    	return 0;
    	fi

    	echo -e "\nNo. = $cdcatnum"
   		echo "Title = $cdtitle"
    	echo "Genre = $cdtype"
    	echo "Artist = $cdartist"

    	if get_confirm ; then
      	  insert_title "No."$cdcatnum,$cdtitle,$cdtype,$cdartist
     	   add_record_tracks $cdcatnum $cdtitle
  	  	fi
	fi

return
}

add_record_tracks() 
{
    local cdcatnum=$1
    local cdtitle=$2
    local cdtrack=1
	echo -e "\nEnter tracks for the No.$cdcatnum CD."
	echo "To quit -> q"
    valid_cdttitle_val $cdcatnum $cdtitle $cdtrack 
}

#############search part#############

search_cd()                        #main search func.
{
    # if [ "$1" = "n" ]; then
    # asklist=n
    # else
    # asklist=y
    # fi
    
    local searchstr=""
    local linesdef=""
    clear
    echo "----Search CD Menu----"
    echo -e "Enter the title you want to search for : \c"
    read searchstr
    
    if [ -z "$searchstr" ]; then        
	    return 0;
    fi

    linesdef=`grep "$searchstr" $title_file | wc -l` #count the number of title that wants to search from file.
    
    case "$linesdef" in     
	    0)  echo "Not found. Please return to the menu "
		    to_return
		    return 0;;
	    *)  echo -e "\n----CD information----"
		    region $searchstr
    esac
    return 0;
}

region()
{
    local searchstr=$1
    local cdcatnum=""
    local cdtitle=""
    local cdtype=""
    local cdartist=""
    grep "$searchstr" $title_file > $temp_file    
    #overlap won't be happen since we'll use overlap_task() func.
    
	# linesfound=$(grep -c ".*" $temp_file)   #count the number of lines that include "."
	# case "$linesfound" in
	# 0)
	# echo "Not found"
	# to_return
	# return 0;;
	#     1)
	# ;;
	# ###todo1    
	#     2) 
	# echo "Not unique"                            
	# 	    echo "Found the following"
	# 	    cat $temp_file
	# 	    to_return
	# 	    return 0;;
	# esac
    
    IFS=","                                                #temporary change Internal Field Separator to comma.

    read cdcatnum cdtitle cdtype cdartist < $temp_file                                                               
    IFS=" "
    
    ###todo2   PPT Ver.
    # if [ -z "$cdcatnum" ]; then                                #if cannot extract(read) $cdcatnum from $temp_file. 
    # 	echo "Could not extract catalog field form $temp_file"   
    # 	to_return
    #  	return 0
    # fi
    ###todo2

    ###todo2   diff. with PPT.
    if valid_extract $cdcatnum $cdtitle $cdtype $cdartist ; then    #add more checking process.
        echo "Could not extract catalog field form $temp_file"    
        to_return
        return 0
    fi
    ###todo2
    

    echo "CD number : $cdcatnum"
    echo "title : $cdtitle"
    echo "type : $cdtype"
    echo -e "artist : $cdartist\n"
    
    ###todo3   PPT Ver.
    # if [ "$asklist" = "y" ]; then
    # 	echo -e "View tracks for this CD? (y/n) \c"
    # 	read x
    # 	if [ "$x" = "y" ]; then
    # 		echo
    # 		list_track_search
    # 		to_return
    # 		echo
    # 	fi
    # fi
    ###todo3

    local x=""
    ###todo3   diff. with PPT.
 
    while (true); do
        echo -e "View tracks for this CD? (y/n) \c"
        read x
        case "$x" in
            y | yes | Y | Yes | YES )
                                        echo -e "\n"
                                        list_track_search $cdtitle
                                        to_return
                                        return 1;;
            n | no | N | No | NO )
                                        echo -e "\n"
                                        return 1;;
            *) echo "Please enter yes or no" ;;
        esac
    done

    ###todo3
}

list_track_search()
{   
    local cdtitle=$1
    local num_tracks=""
    grep "$cdtitle" $track_file > $temp_file
    set $(wc -l $temp_file)
	num_tracks=$1
    
    if [ "$num_tracks" == "0" ] ; then
            echo "no tracks found for $cdtitle"
      else {
         echo -e "-----Track List------"
         echo -e "\nCD title : $cdtitle\n"
 		 echo "num | track "
		 cut -d "," -f3 $temp_file > $temp1_file
		 cut -d "," -f4 $temp_file > $temp2_file
		 paste $temp1_file  $temp2_file
		 } | ${PAGER:-more}
      fi
}

###todo5     this func. is just for updata_cd func.
list_track(){
    local cdcatnum=$1
    local num_tracks=""
    grep "No.$cdcatnum," $track_file > $temp_file
 	set $(wc -l $temp_file)
 	num_tracks=$1
       if [ "$num_tracks" == "0" ] ; then
          echo "no tracks found for No.$cdcatnum"
       else {
          echo "-----Track List------"
          echo "CD number : No.$cdcatnum" 
  		 echo "num   |  track "
 		 cut -d "," -f3 $temp_file > $temp1_file
 		 cut -d "," -f4 $temp_file > $temp2_file
 		 paste $temp1_file $temp2_file
 		 } | ${PAGER:-more}       
       fi
    return
 }
###todo5


###########Update part###############
update_cd()
{
    local cdtitle=""
    local cdtitle_chk=""
    local cdcatnum=""
    clear
    echo "----Update CD Menu----"
    while (true); do
        echo -e "CD title : \c"
        read cdtitle
        cdtitle_chk=${cdtitle//[A-Z,a-z]/}
        if [ ! -z "$cdtitle_chk" ]; then
                echo "Please type only alphabet."
                continue
        fi
        if [ "$cdtitle" != "" ]; then
            if [ "$(grep "$cdtitle" $title_file | wc -l)" == "0" ] ; then
            return 0
            fi
            echo "Current tracks"
            list_track_search $cdtitle
            break
        else
            to_return
        fi
    done
    if [ "$num_tracks" != "0" ]; then    #take this value from list_track_search() func.
        echo -e "\nThis will re−enter the tracks for CD -> $cdtitle."
           get_confirm && {
            grep -v "$cdtitle" $track_file > $temp_file             #temporary move other track files to tmp file.
                                                                    #then paste it to original $track_file.
            grep "$cdtitle" $track_file > $temp1_file
            cut -d "," -f1 $temp1_file > $temp2_file
            mv $temp_file $track_file
            cdcatnum=`cut -d "." -f2 $temp2_file | uniq`

            add_record_tracks $cdcatnum $cdtitle
        }
    else
        to_return
    fi
    return
}

#############delete part#############finish

delete_cd(){
    local count=""
    clear
    echo "----Delete CD Menu----"
    view
    count=$?
    if [ "$(grep "^No.$count\>" $title_file | wc -l)" = "1" ]; then
    get_confirm && {
        grep -v "^No.${count}," $title_file > $temp_file
        mv $temp_file $title_file
        grep -v "^No.${count}," $track_file > $temp_file
        mv $temp_file $track_file
        echo "No.$count CD removed"
    }
        echo
        to_return
    fi
    return
}

view()    #show all CD.
{
    local cdcatnum=""
    if test -z $title_file ; then
        return 0;
    fi

    echo "num  |  title |  genre | artist  "
    cut -d "," -f1 $title_file > $temp1_file
    cut -d "," -f2 $title_file > $temp2_file
    cut -d "," -f3 $title_file > $temp3_file
    cut -d "," -f4 $title_file > $temp4_file
    paste $temp1_file $temp2_file $temp3_file $temp4_file
    valid_cdcatnum_val "mode2"                #call valid_cdcatnum_val as delete mode.
    cdcatnum=$?
    
    grep "^No.${cdcatnum}," $track_file > $temp_file
    echo "CDnum | tracknum | title |  "
    cut -d "," -f1 $temp_file > $temp1_file
    cut -d "," -f3 $temp_file > $temp2_file
    cut -d "," -f4 $temp_file > $temp3_file
    paste -d '\t' $temp1_file $temp2_file $temp3_file


    return "$cdcatnum"
}

#########sort part#############finish
sort_cd()
{
    clear
    echo "----Sort CD Menu----"
    echo "Please choose sort type"
    echo "a)CD number"
    echo "b)title"
    echo "c)genre"
    echo "d)artist"
    echo "etc)return to main menu"
    echo -e "Sorting method : \c"
    read x

    case $x in
        a)num_sort;;
        b)title_sort;;
        c)genre_sort;;
        d)artist_sort;;
        *)return
    esac

    view_sort

}

view_sort()        # use just $title_file since it is already sorted.
{
    echo "num   |  title |  type |  artist  "

    cut -d "," -f1 $title_file > $temp1_file
    cut -d "," -f2 $title_file > $temp2_file
    cut -d "," -f3 $title_file > $temp3_file
    cut -d "," -f4 $title_file > $temp4_file
    paste $temp1_file $temp2_file $temp3_file $temp4_file
    to_return
    return
}

num_sort(){    # sort by CD Numb.
    sort -b -t "," -k 1 $title_file > $temp_file
    mv $temp_file $title_file

    return
}

title_sort(){    # sort by title
    sort -b -t "," -k 2 $title_file > $temp_file
    mv $temp_file $title_file

    return
}

genre_sort(){    # sort by genre
    sort -b -t "," -k 3 $title_file > $temp_file
    mv $temp_file $title_file

    return
}

artist_sort(){    # sort by artist
    sort -b -t "," -k 4 $title_file > $temp_file
    mv $temp_file $title_file

    return
}


#############main#############
main_menu(){
    clear
    echo ""
    echo ""
    echo "  A)Add CD"
    echo "  B)Search CD"
    echo "  C)Delete CD"
    echo "  D)SORT CD"
    echo "  E)Track List"
    echo "  F)Update CD"
    echo ""
    echo "  Q)Quit"
    echo -e "Choice Menu : \c"
	# rm -f $temp_file
	# rm -f $temp1_file
	# rm -f $temp2_file
	# rm -f $temp3_file
	# rm -f $temp4_file
    return
}

if [ ! -f $title_file ]; then    
    touch $title_file
fi

if [ ! -f $track_file ]; then
    touch $track_file
fi

clear

echo 
echo ""
echo ""
echo "       UOU_Linux_Group 5      "
echo "   Term_Project - CD_manager "
echo ""
echo "           Loading...        "
echo ""
echo ""

sleep 1
quit=n

while [ "$quit" != "y" ] ;
do
    main_menu
	read menu_choice
	case $menu_choice in
	    A | a) add_cd;;
		B | b) search_cd;;
		C | c) delete_cd;;
		D | d) sort_cd;;
		E | e) clear
			   echo "----Track List Menu----" 
			   echo -e "CD number : \c"
			    read cdcatnum
				list_track $cdcatnum   #$cdcatnum will be used. (Not $cdtitle)
				to_return;;
		F | f) update_cd;;
		Q | q) quit=y;;
	esac
done

rm -f $temp_file
rm -f $temp1_file
rm -f $temp2_file
rm -f $temp3_file
rm -f $temp4_file
echo "Temp file removed"
exit 0;
