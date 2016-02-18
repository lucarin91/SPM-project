use strict;
use warnings FATAL => 'all';
my $r = "0.000135868:0.023796511:\n0.029\n";
my @value = split /:/, $r;

foreach my $item (@value){
    print $item."\n";
}

1;