for(let i=1;i<=array32u.length;i++) {
	var count=0;
	var j=i;
    if ((array32u[j+4]>>24)==-128) while (true) {
		if ((array32u[j+4]>>24)==-128) {
			j+=13;
			count++;
		}
		else {
			if (count>20) console.log(postopsxe(i<<2)+"  -> "+postopsxe(j<<2)+" "+count);
			break;
		}
    }
}