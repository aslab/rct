flt=red-blue-green;
height=size(flt,1);
width=size(flt,2);
for j=1:height
    for i=1:width
        if flt(j,i) < 0
            flt(j,i)=0;
        end
    end
end

%Centro de gravedad
[a,b] = ndgrid(1:height,1:width);
Mt = sum(flt(:));
h = sum(flt(:) .* a(:)) / Mt;
w = sum(flt(:) .* b(:)) / Mt;
