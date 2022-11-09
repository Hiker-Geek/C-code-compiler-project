int x;
int y[5];
void main(void)
begin
	x = 1;
	while x >= 5 do
	begin
		if x == 5 then
		begin
			y[x] = 3;
		end
		else
		begin
			y[x] = x*2;
		end
		x = x+1;
	end
end	
			
