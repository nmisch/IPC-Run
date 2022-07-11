use strict;
use warnings FATAL => "uninitialized";;

use IPC::Run;
use Test::More tests => 3;

my $h = IPC::Run::start( [ 'perl', '-le', 'for (1..10) { print $_ }' ], '>pipe', my $fh );
ok $h;
my @content = <$fh>;
is_deeply \@content, [ map { "$_\n" } (1..10) ];
ok $h->finish;
