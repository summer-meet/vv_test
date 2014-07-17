program word(input,output);
const
	c:array[1..5]of longint=(2,3,5,7,11);{这个不行，至少判断50次}
var
  s:ansistring;
  tot:array['a'..'z'] of longint;
  num:longint;
function modular_exp(a,p,k:longint):int64;
  var
    t,ans:int64;
  begin
	t:=a; ans:=1;
	while p>0 do
		begin
			if (p and 1=1) then
				ans:=((ans mod k)*(t mod k)) mod k;
			t:=((t mod k)*(t mod k)) mod k;
			p:=p>>1;
		end;
	exit(ans);
end;
function miller_rabbin(n:longint):boolean;
  var
	i:longint;
  begin
	if n<=1 then exit(false);
	if n in [2,3,5,7,11] then exit(true);
    for i:=1 to 5 do
		if modular_exp(c[i],n-1,n)<>1 then exit(false);
    exit(true);
end;
procedure count;
  var
    i,l,max,min:longint;
    j:char;
  begin
    l:=length(S);
    for i:=1 to l do inc(tot[s[i]]);
    max:=0; min:=maxlongint;
    for j:='a' to 'z' do
      begin
        if tot[j]>max then max:=tot[j];
        if (tot[j]<min)and(tot[j]>0) then min:=tot[j];
      end;
    num:=max-min;
  end;
begin
  assign(input,'word.in'); reset(input);
  assign(output,'word.out'); rewrite(output);
  read(s);
  count;
  if miller_rabbin(num)
    then
      begin
        writeln('Lucky Word');
        writeln(num);
      end
    else
      begin
        writeln('No Answer');
        writeln(0);
      end;
  close(input); close(output);
end.
