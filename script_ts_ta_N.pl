#!/bin/perl
use strict;
use warnings;
use constant N => 10;
my $filename = shift or die "Usage: $0 FILENAME NUMBER\n";
my $size = shift or die "Usage: $0 FILENAME NUMBER\n";
my $N = shift || N;

my @json1 = ();
foreach my $n (1000,5000,10000,50000,100000) {
  my @json = ();
  foreach my $p (1,5,10,15,20,25,30,35,40,45,50,55,60,65) {
    my @sum=(0,0,0);
    my @timings = ();

    print STDERR "$p: ";
    foreach my $i (1..$N) {
      # \time --format="%E" ./main.out --step 1000 --height 1000 --width 1000 --thread 16
      my $r=`\\ssh mic1 "TIMEFORMAT=%R && time ./$filename $p $size $n" 2>&1`;
      my @value = split /:/, $r;
      my $j = 0;
      foreach my $item (@value){
        $item =~ s/^\s+|\s+$//g;
        print STDERR $item." ";
        $sum[$j]=$sum[$j] + $item;
        $j++;
      }
      push @timings, "[" . join(", ", @value) . "]";
    }
    print STDERR "\n";
    my @sorted = sort @timings;
    my @avg=(0,0,0);
    for(my $i=0;$i<@sum;++$i){
      $avg[$i]=$sum[$i]/$N;
    }
    # my $avg = $sum/$N;
    # push @json, "[$p, @avg, " . join(", ", @timings) . "]";
    push @json, "[$p, [" . join(", ", @avg) . "], " . join(", ", @sorted) . "]";
  }
  push @json1, "[\n" . join(",\n", @json) . "\n]";
}
print "[\n" . join(",\n", @json1) . "\n]";


