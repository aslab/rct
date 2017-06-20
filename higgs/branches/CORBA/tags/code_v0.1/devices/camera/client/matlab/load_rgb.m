load red; load green; load blue;
rgb=red;rgb(:,:,2)=green;rgb(:,:,3)=blue;
rgb=rgb ./ max(max(max(rgb)));
image(rgb)