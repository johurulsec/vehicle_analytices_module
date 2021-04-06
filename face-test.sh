#!/bin/bash

for file in /home/sigmind/WC-Face-Multithread/wc-Fr-MT/watchcam11/faceUnmusk/Beforetest/*.png
 do   name=$(basename "$file")
 i=0   
 outCrop="/home/sigmind/Music/facedetect-master/face-test/$name"   
 outMask="/home/sigmind/Music/facedetect-master/face-test-mask/$name" 
 outMaskCrop="/home/sigmind/Music/facedetect-master/face-test-crop-mask/$name"
 outCrop256="/home/sigmind/Music/facedetect-master/face-test-crop-mask-resize/$name" 
 outMaskCrop256="/home/sigmind/Music/facedetect-master/face-test-crop-mask-final/$name" 

echo "Face Found"
#cp "$file" "$outCropped"
#cp "$file" "$outMasked"

# echo "Face Cropped"
# done
#python facedetect "$file" | while read x y w h; do convert "$file" -crop ${w-20}x${h-20}+${x}+${y} "$outCrop";  done;
# python facedetect "$file" | while read x y w h; do     mogrify -gravity West -region "${w}x${h+50}+${x}+${y+40}" -fill black +opaque black  "$outMasked";   done;
# python facedetect "$file" | while read x y w h; do     mogrify -gravity West -region "${w-5}x${h+50}+${x}+${y+40}" -blur 0x12  "$outMasked";   done;
python facedetect "$file" | while read x y w h; do  convert "$file" -crop ${w-20}x${h-20}+${x}+${y} "$outCrop"; convert "$outCrop" -resize 128x128! "$outCrop256";
cp "$file" "$outMask";  mogrify -gravity West -region "${w}x${h+200}+${x}+${y+140}" -fill red  +opaque red  "$outMask"; convert "$outMask" -crop ${w-20}x${h-20}+${x}+${y} "$outMaskCrop"; convert "$outMaskCrop" -resize 128x128! "$outMaskCrop256";  done;
#python facedetect "$file" | while read x y w h; do convert "$file" -crop ${w-20}x${h-20}+${x}+${y} "$outCrop"; cp "$outCrop" "$outMasked";  done;
echo "Images Saved"   
i=$(($i+1))
 
done

# mogrify -type Grayscale *.jpg  for Greyscale conversion
