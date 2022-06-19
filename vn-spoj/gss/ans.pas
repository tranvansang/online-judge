{$MODE OBJFPC}
program gss;
const
  inputfile = '';
  outputfile = '';
  nmax= 50000;
  lognmax = 4;
  nnode = nmax * lognmax;
type
  tnode = record
    l, r, a, s: integer;
    end;
var
  it: array[1..nnode] of tnode;
  maxt: array[1..nnode] of integer;
  t: array[1..nmax] of integer;
  fi, fo: textfile;
  n, m: integer;

procedure solve;
var
  i, j, x, y: integer;

  function max(x, y: integer): integer;
  begin
    if x >= y then result := x
    else result := y;
  end;

  procedure update(k, l, h: integer);
  var
    k1, mid: integer;
  begin
    if l = h then
      begin
        it[k].s := t[l];
        maxt[k] := t[l];
        if t[l] > 0 then
          begin
            it[k].l := t[l];
            it[k].r := t[l];
            it[k].a := t[l];
          end;
        exit;
      end
    else
      begin
        k1 := k shl 1;
        mid := (l + h) shr 1;
        update(k1, l, mid);
        update(k1 + 1, mid + 1, h);
        maxt[k] := max(maxt[k1], maxt[k1 + 1]);
        it[k].s := it[k1].s + it[k1 + 1].s;
        it[k].l := max(it[k1].l, it[k1].s + it[k1 + 1].l);
        it[k].r := max(it[k1 + 1].r, it[k1 + 1].s + it[k1].r);
        it[k].a := max(max(it[k1].a, it[k1 + 1].a), it[k1].r + it[k1 + 1].l);
      end;
  end;

  function getr(k, l, h: integer): integer;
  var
    mid, k1: integer;
  begin
    if (y < h) or (x > h) then exit(0);
    if x <= l then exit(it[k].r);
    mid := (h + l) shr 1;
    k1 := k shl 1;
    result := getr(k1 + 1, mid + 1, h);
    if x <= mid then result := max(result, getr(k1, l, mid) + it[k1 + 1].s);
  end;

  function getl(k, l, h: integer): integer;
  var
    mid, k1: integer;
  begin
    if (x > l) or (y < l) then exit(0);
    if h <= y then exit(it[k].l);
    mid := (h + l) shr 1;
    k1 := k shl 1;
    result := getl(k1, l, mid);
    if mid < y then
      result := max(result, it[k1].s + getl(k1 + 1, mid + 1, h));
  end;

  function get(k, l, h: integer): integer;
  var
    k1, mid: integer;
  begin
    if (h < x) or (l > y) then exit(0);
    if (x <= l) and (h <= y) then exit(it[k].a);
    mid := (h + l) shr 1;
    k1 := k shl 1;
    if y <= mid then result := get(k1, l, mid)
    else
      if mid < x then result := get(k1 + 1, mid + 1, h)
      else
        result := max(max(getr(k1, l, mid)+ getl(k1 + 1, mid + 1, h),
          get(k1, l, mid)), get(k1 + 1, mid + 1, h));
  end;

  function getmax(k, l, h: integer): integer;
  var
    mid: integer;
  begin
    if (x > h) or (y < l) then exit(low(integer));
    if (x <= l) and (h <= y) then exit(maxt[k]);
    mid := (h + l) shr 1;
    result := max(getmax(k shl 1, l, mid), getmax((k shl 1) + 1, mid + 1, h));
  end;

begin
  readln(fi, n);
  for i := 1 to n do read(fi, t[i]);
  update(1, 1, n);
  readln(fi);
  readln(fi, m);
  for i := 1 to m do
    begin
      readln(fi, x, y);
      j := get(1, 1, n);
      if j > 0 then writeln(fo, j)
      else writeln (fo, getmax(1, 1, n));
    end;
end;

begin
  assignfile(fi, inputfile); reset(fi);
  assignfile(fo, outputfile); rewrite(fo);
  solve;
  closefile(fi); closefile(fo);
end.