#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kstring.h"
#include "printbuf.h"
#include "dexter.h"
#include "xml2json.h"
#include <libxslt/xslt.h>
#include <libxslt/xsltInternals.h>
#include <libxslt/transform.h>
#include <libxml/parser.h>
#include <libxml/HTMLparser.h>
#include <libxml/HTMLtree.h>
#include <libxml/xmlwriter.h>
#include <json/json.h>

struct json_object * recurse(xmlNodePtr);

void dex_error(char* msg){
	fprintf(stderr, "%s\n", msg);
  exit(1);
}

int main (int argc, char **argv) {
  if(argc != 3) {
    printf("Usage: dexter DEX HTML\n");
    exit(1);
  }
  struct printbuf *buf = printbuf_new();
  
  FILE * fd = fopen(argv[1], "r");
  
  printbuf_file_read(fd, buf);
  dexPtr dex = dex_compile(buf->buf, "");
	xmlDocPtr xml = dex_parse_file(dex, argv[2], 1);
  
  struct json_object *json = xml2json(xml->children->children);
  printf("%s\n", json_object_to_json_string(json));

	return 0;
}