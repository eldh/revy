(window.webpackJsonp=window.webpackJsonp||[]).push([[0],[,,,,,,function(e,t,r){"use strict";var n=r(2),i=r(5),o=r(1),a=r(0),c=r(7),l=r(16);function s(e,t,r,o,a,l,s,u,d,v,m,h,f,g,y,p,k){var b=c.Styles[6](g);return i.concat([[n.alignSelf(t),[n.alignItems(e),[n.backgroundColor(c.Styles[7](void 0,void 0,o)),[n.alignContent(r),[n.color(c.Styles[7](void 0,void 0,a)),[n.height(f),[n.overflow(y),[n.borderRadius(p),[n.flexShrink(u),[n.flexDirection(v),[n.flexGrow(l),[n.flexWrap(s),[n.justifyContent(d),0]]]]]]]]]]]]],[c.Styles[4](h),[c.Styles[5](m),[b,0]]]])}var u=function(e){var t=e.tag,r=void 0!==t?t:"div";e.a11yTitle;var c=e.style,u=void 0!==c?c:0,d=e.align,v=void 0!==d?d:662439529,m=e.alignSelf,h=void 0!==m?m:-1065951377,f=e.alignContent,g=void 0!==f?f:662439529,y=e.backgroundColor,p=void 0!==y?y:13,k=e.color,b=void 0!==k?k:6,S=e.grow,_=void 0!==S?S:1,x=e.wrap,E=void 0!==x?x:-822134326,C=e.shrink,w=void 0!==C?C:0,B=e.justify,R=void 0!==B?B:662439529,T=e.direction,$=void 0!==T?T:-963948842,z=e.p,G=void 0!==z?z:o.__(0,[1]),F=e.m,P=void 0!==F?F:o.__(0,[1]),I=e.h,L=void 0!==I?I:-1065951377,H=e.w,M=void 0!==H?H:6,N=e.overflow,W=void 0!==N?N:-1065951377,O=e.borderRadius,V=void 0!==O?O:n.px(0),j=e.domProps,D=e.children,A=i.concat([s(v,h,g,p,b,_,E,w,R,$,G,P,L,M,W,V),[u,0]]);return a.createElement(l.make,{tag:r,style:A,domProps:j,children:D})};t.useBoxStyle=s,t.make=u},function(e,t,r){"use strict";var n=r(2),i=r(5),o=r(23),a=r(3),c=r(0),l=r(24),s=r(13),u=r(27),d=r(10),v=r(11),m=r(15),h=v.create("Core-Revy.InvalidValue");function f(e,t){return[n.media("(min-width: 30em)",t[1]),[n.media("(min-width: 50em)",t[2]),t[0]]]}function g(e,t,r){return s.caml_lessthan(r,e)?e:s.caml_greaterthan(r,t)?t:r}function y(e,t){if("number"===typeof t)return t;var r=t[0];if(r>=-878128971){if(5197569!==r){if(5692173!==r)return t;var n=t[1];return[5692173,[g(0,255,n[0]+e|0),g(0,255,n[1]+e|0),g(0,255,n[2]+e|0)]]}var i=t[1];return[5197569,[i[0],i[1],g(0,100,i[2]+e|0)]]}if(-988425664!==r){if(r>=-878128972){var o=t[1];return[-878128972,[g(0,255,o[0]+e|0),g(0,255,o[1]+e|0),g(0,255,o[2]+e|0),o[3]]]}return t}var a=t[1];return[-988425664,[a[0],a[1],g(0,100,a[2]+e|0),a[3]]]}function p(e,t){return y(d.imul(e,-1),t)}function k(e){var t=e[0][10];if("number"===typeof t)return!0;var r=t[0];if(r>=-878128971){if(5197569!==r){if(5692173!==r)return!0;var n=t[1];return u.fromRGB([n[0],n[1],n[2]])[0]>50}return t[1][2]>50}if(-988425664!==r){if(r>=-878128972){var i=t[1];return u.fromRGB([i[0],i[1],i[2]])[0]>50}return!0}return t[1][2]>50}function b(e,t){if("number"===typeof t)return t;var r=t[0],i=0;if(r>=-878128971)if(5197569!==r){if(5692173!==r)return t;i=2}else i=1;else if(-988425664!==r){if(!(r>=-878128972))return t;i=2}else i=1;switch(i){case 1:var o=t[1];return n.hsla(o[0],o[1],o[2],e);case 2:var a=t[1];return n.rgba(a[0],a[1],a[2],e)}}function S(e,t,r,n){var i,o=void 0!==t?t:1,c=void 0!==r?r:0,l=k(e)?p:y;if("number"===typeof n)switch(n){case 0:i=e[0][0];break;case 1:i=e[0][2];break;case 2:i=e[0][4];break;case 3:i=e[0][6];break;case 4:i=e[0][8];break;case 5:i=e[0][10];break;case 6:i=e[0][1];break;case 7:i=e[0][3];break;case 8:i=e[0][7];break;case 9:i=e[0][9];break;case 10:i=e[0][5];break;case 11:i=e[0][11];break;case 12:i=e[0][12];break;case 13:i=582626130}else i=n.tag?n[0]:S(e,void 0,n[0],n[1]);return(1!==o?function(e){return b(o,e)}:function(e){return e})(a._1(function(e){return l(c,e)},i))}function _(e,t){var r;switch(t){case 0:r=e[1][0];break;case 1:r=e[1][1];break;case 2:r=e[1][2];break;case 3:r=e[1][3]}return l.concat(", ",r)}function x(e,t){return n.px(Math.pow(e[2],t)*e[3]|0)}function E(e,t){switch(t){case 0:return-21160922;case 1:return-184774442;case 2:return 812216871;case 3:return-1055161979;case 4:return-81801163}}function C(e,t,r){var i=void 0!==t?t:0,o=function(t){return n.px(d.imul(e[4],t)-i|0)};if("number"!==typeof r)return r.tag?o(6):o(r[0]);switch(r){case 0:return n.auto;case 1:return n.px(0);case 2:return o(1);case 3:return o(2);case 4:return o(3);case 5:return o(6);case 6:return o(8);case 7:return o(10)}}function w(e,t){for(;;){var r=t;if(a._1(e,r))return r;t=r+1|0}}function B(e){if("number"===typeof e)throw[h,"Not a pixel value"];if(25096!==e[0])throw[h,"Not a pixel value"];return e[1]}function R(e,t,r,i){var o=void 0!==t?t:n.px(0),a=void 0!==r?r:0,c=w(function(t){return d.imul(t,e[4])>1.25*B(o)},0)+a|0;return n.px(d.imul(e[4],c))}var T=[g,function(e){return g(0,255,e)},function(e){return g(0,100,e)},y,p,function(e,t){if("number"===typeof t)return y(e,t);var r=t[0],n=0;if(r>=-878128971)if(5197569!==r){if(5692173!==r)return y(e,t);n=2}else n=1;else if(-988425664!==r){if(!(r>=-878128972))return y(e,t);n=2}else n=1;switch(n){case 1:return t[1][2]>50?p(e,t):y(e,t);case 2:var i=t[1];return u.toCssRGB(u.highlight(e,u.fromRGB([i[0],i[1],i[2]])))}},k,b,S,_,x,E,C,w,B,R];function $(e,t,r,i,o,a,c){var l=void 0!==e?e:1.25,s=void 0!==t?t:16,d=void 0!==r?r:4,v=void 0!==i?i:[["-apple-system",["BlinkMacSystemFont",["sans-serif",0]]],["-apple-system",["BlinkMacSystemFont",["sans-serif",0]]],["monospace",0],["-apple-system",["BlinkMacSystemFont",["sans-serif",0]]]];return[void 0!==o?o:[u.toCssRGB(u.lighten(25,u.fromRGB([36,133,222]))),n.rgb(0,0,0),u.toCssRGB(u.lighten(25,u.fromRGB([20,10,0]))),n.rgb(255,255,255),u.toCssRGB(u.lighten(25,u.fromRGB([44,173,2]))),n.rgb(0,0,0),u.toCssRGB(u.lighten(25,u.fromRGB([214,149,5]))),n.rgb(0,0,0),u.toCssRGB(u.lighten(25,u.fromRGB([211,26,26]))),n.rgb(0,0,0),n.rgb(255,255,255),n.rgb(40,40,40),n.rgb(130,130,130)],v,l,s,d,void 0!==a?a:960]}var z=[$(void 0,void 0,void 0,void 0,void 0,void 0)],G=c.createContext($(void 0,void 0,void 0,void 0,void 0,void 0)),F=G.Provider;var P=[G,F,[function(e){var t=e.value,r=e.children;return m.use(F,{value:t,children:r})}]];function I(e,t){var r=function(t){return C(e,void 0,t)};if("number"===typeof t)return[n.margin(-1065951377),0];switch(0|t.tag){case 0:return[n.margin(r(t[0])),0];case 1:return[n.marginTop(r(t[0])),0];case 2:return[n.marginBottom(r(t[0])),0];case 3:return[n.marginLeft(r(t[0])),0];case 4:return[n.marginRight(r(t[0])),0];case 5:return[n.margin2(r(t[1]),r(t[0])),0];case 6:return[n.margin4(r(t[1]),r(t[2]),r(t[3]),r(t[0])),0];case 7:return f(0,[I(e,t[0]),I(e,t[1]),I(e,t[2])])}}function L(e,t){switch(0|t.tag){case 0:return[n.padding(C(e,void 0,t[0])),0];case 1:return[n.paddingTop(C(e,void 0,t[0])),0];case 2:return[n.paddingBottom(C(e,void 0,t[0])),0];case 3:return[n.paddingLeft(C(e,void 0,t[0])),0];case 4:return[n.paddingRight(C(e,void 0,t[0])),0];case 5:return[n.padding2(C(e,void 0,t[1]),C(e,void 0,t[0])),0];case 6:return[n.padding4(C(e,void 0,t[1]),C(e,void 0,t[2]),C(e,void 0,t[3]),C(e,void 0,t[0])),0];case 7:return f(0,[L(e,t[0]),L(e,t[1]),L(e,t[2])])}}function H(e,t){var r=e[5];if("number"===typeof t)switch(t){case 0:return[n.width(n.pct(12.5)),0];case 1:return[n.width(n.pct(100/6)),0];case 2:return[n.width(n.pct(25)),0];case 3:return[n.width(n.pct(100/3)),0];case 4:return[n.width(n.pct(50)),0];case 5:return[n.maxWidth(n.px(r)),[n.width(n.pct(100)),0]];case 6:return[n.width(-1065951377),0]}else switch(0|t.tag){case 0:return[n.width(n.pct(t[0])),0];case 1:return[n.width(t[0]),0];case 2:return f(0,[H(e,t[0]),H(e,t[1]),H(e,t[2])])}}function M(e){var t=Object.keys(e)[0].replace(/([a-z])([A-Z])/g,"$1-$2").toLowerCase();return window.document.body.style[t]=e[Object.keys(e)[0]],0}function N(e){var t=window.matchMedia(e),r=c.useState(function(){return t.matches}),n=r[1];return c.useLayoutEffect(function(){var e=t.addListener(function(e){return a._1(n,function(e){return t.matches})});return function(r){return t.removeListener(e)}},[]),r[0]}var W=[function(e,t){return C(e,void 0,t)},I,L,H,function(e){return I(c.useContext(G),e)},function(e){return L(c.useContext(G),e)},function(e){return H(c.useContext(G),e)},function(e,t,r){var n=void 0!==e?e:0,i=void 0!==t?t:1;return S(c.useContext(G),i,n,r)},function(e,t){var r=void 0!==e?e:0;return C(c.useContext(G),r,t)},function(e){return _(c.useContext(G),e)},function(e){return x(c.useContext(G),e)},function(e){return E(c.useContext(G),e)},function(e,t,r){var i=void 0!==e?e:n.px(0),o=void 0!==t?t:0;return R(c.useContext(G),i,o)},function(e){return k(c.useContext(G))},M,N,function(e){return N("(prefers-color-scheme: dark)")},function(e){return c.useLayoutEffect(function(){i.map(function(e){return M(n.toJson([e,0]))},e)},o.of_list(e)),0}];t.InvalidValue=h,t.Layout=[],t.Space=[],t.Type=[],t.Color=[],t.responsive=f,t.Private=T,t.make=$,t.DefaultTheme=z,t.Context=P,t.Styles=W},,function(e,t,r){"use strict";var n=r(2),i=r(5),o=r(1),a=r(0),c=r(6),l=r(7),s=r(11),u=r(15),d=s.create("Text-Revy.InvalidValue");function v(e,t,r,i,o,a){var c=void 0!==r?r:0,s=l.Styles[10](e);return[n.color(l.Styles[7](void 0,void 0,t)),[n.fontSize(s),[n.fontFamily(l.Styles[9](c)),[n.lineHeight(l.Styles[12](s,i,0)),[n.fontWeight(l.Styles[11](o)),0]]]]]}var m=[function(e){var t=e.weight,r=void 0!==t?t:2,o=e.tag,a=void 0!==o?o:"span",c=e.size,l=void 0!==c?c:0,s=e.style,d=e.lineHeight,m=void 0!==d?d:0,h=e.color,f=void 0!==h?h:11,g=e.children,y=v(l,f,void 0,m,r);return u.use(a,{className:n.style(void 0!==s?i.concat([y,[s,0]]):y),children:g})}];var h=[function(e){var t=e.weight,r=void 0!==t?t:2,a=e.tag,c=void 0!==a?a:"div",s=e.m,d=void 0!==s?s:o.__(0,[0]),m=e.size,h=void 0!==m?m:0,f=e.style,g=e.lineHeight,y=void 0!==g?g:0,p=e.color,k=void 0!==p?p:11,b=e.children,S=v(h,k,void 0,y,r),_=l.Styles[4](d);return u.use(c,{className:n.style(i.concat(void 0!==f?[S,[_,[f,0]]]:[S,[_,0]])),children:b})}];var f=[function(e){var t=e.weight,r=void 0!==t?t:2,a=e.tag,c=void 0!==a?a:"p",s=e.m,d=void 0!==s?s:o.__(6,[1,1,1,4]),m=e.size,h=void 0!==m?m:0,f=e.style,g=e.lineHeight,y=void 0!==g?g:0,p=e.color,k=void 0!==p?p:11,b=e.children,S=v(h,k,void 0,y,r),_=l.Styles[4](d);return u.use(c,{className:n.style(i.concat(void 0!==f?[S,[_,[f,0]]]:[S,[_,0]])),children:b})}];var g=[function(e){var t=e.weight,r=void 0!==t?t:2,s=e.tag,d=void 0!==s?s:"pre",m=e.m,h=void 0!==m?m:o.__(5,[1,4]),f=e.size,g=void 0!==f?f:0,y=e.style,p=e.lineHeight,k=void 0!==p?p:0,b=e.color,S=void 0!==b?b:11,_=e.children,x=v(g,S,2,k,r),E=l.Styles[4](o.__(0,[1])),C=l.Styles[5](o.__(0,[4]));return a.createElement(c.make,{style:[n.width(n.pct(100)),[n.overflow(-949692403),0]],backgroundColor:o.__(1,[l.Styles[7](7,void 0,5)]),m:h,borderRadius:n.px(6),children:u.use(d,{className:n.style(i.concat(void 0!==y?[x,[E,[C,[y,0]]]]:[x,[E,[C,0]]])),children:_})})}],y=function(e){var t=e.weight,r=void 0!==t?t:2,o=e.size,a=void 0!==o?o:0,c=e.tag,l=void 0!==c?c:"span",s=e.style,d=e.lineHeight,m=void 0!==d?d:0,h=e.color,f=void 0!==h?h:11,g=e.children,y=v(a,f,void 0,m,r);return u.use(l,{className:n.style(void 0!==s?i.concat([y,[s,0]]):y),children:g})};t.InvalidValue=d,t.useTextStyles=v,t.make=y,t.$$String=m,t.Block=h,t.Paragraph=f,t.Code=g},,,,,,function(e,t,r){"use strict";var n=r(0);var i=function(e){var t=e.tag,r=void 0!==t?t:"div",i=e.props;return n.createElement(r,i)};t.make=i,t.use=function(e,t){return n.createElement(e,t)}},function(e,t,r){"use strict";var n=r(2),i=r(5),o=r(8),a=r(15),c=[n.display(-1010954439),[n.boxSizing(9307263),0]];var l=function(e){var t=e.tag,r=void 0!==t?t:"div",l=e.onPress,s=void 0!==l?o.valFromOption(l):void 0;e.a11yTitle;var u=e.style,d=void 0!==u?u:0,v=e.domProps,m=void 0!==v?o.valFromOption(v):void 0,h={children:e.children,onClick:s,className:n.style(i.concat([d,[c,0]]))};return a.use(r,void 0!==m?Object.assign(o.valFromOption(m),h):h)};t.defaultStyles=c,t.make=l},function(e,t,r){"use strict";var n=r(1),i=r(0),o=r(9),a=r(8);var c=function(e){var t,r=e.level,c=void 0!==r?r:0,l=e.style,s=e.m,u=void 0!==s?s:n.__(5,[1,1]),d=e.children;switch(c){case 0:t=[5,3,11,"h1"];break;case 1:t=[4,3,11,"h2"];break;case 2:t=[3,3,11,"h3"];break;case 3:t=[2,3,11,"h4"];break;case 4:t=[1,3,11,"h5"]}var v={weight:t[1],tag:t[3],m:u,size:t[0],color:t[2],children:d};return void 0!==l&&(v.style=a.valFromOption(l)),i.createElement(o.Block[0],v)};t.make=c},function(e,t,r){"use strict";var n=r(6),i=r(61),o=r(29),a=r(62),c=r(9),l=r(16),s=r(63),u=r(17),d=r(64),v=r(15),m=r(28),h=r(19),f=[n.useBoxStyle,n.make],g=[s.useButtonStyles,s.make,s.Link],y=[i.useCardStyle,i.make],p=[m.make],k=[v.make,v.use],b=[u.make],S=[o.make],_=[a.useLinkStyle,a.make,a.Button],x=[c.InvalidValue,c.useTextStyles,c.make,c.$$String,c.Block,c.Paragraph,c.Code],E=[d.useInputStyles,d.Input,d.Label],C=[h.make],w=[l.defaultStyles,l.make];t.Box=f,t.Button=g,t.Card=y,t.ComponentsCard=p,t.EscapeHatch=k,t.Heading=b,t.Hero=S,t.Link=_,t.$$Text=x,t.TextInput=E,t.TouchableOpacity=C,t.View=w},function(e,t,r){"use strict";var n=r(2),i=r(5),o=r(1),a=r(3),c=r(0),l=r(6),s=r(16);var u=function(e){var t=e.tag,r=void 0!==t?t:"div";e.a11yTitle;var u,d=e.style,v=void 0!==d?d:0,m=e.align,h=void 0!==m?m:662439529,f=e.alignSelf,g=void 0!==f?f:-1065951377,y=e.alignContent,p=void 0!==y?y:662439529,k=e.backgroundColor,b=void 0!==k?k:13,S=e.color,_=void 0!==S?S:6,x=e.grow,E=void 0!==x?x:1,C=e.wrap,w=void 0!==C?C:-822134326,B=e.shrink,R=void 0!==B?B:0,T=e.justify,$=void 0!==T?T:662439529,z=e.direction,G=void 0!==z?z:-963948842,F=e.onlyFocusOnTab,P=void 0===F||F,I=e.p,L=void 0!==I?I:o.__(0,[1]),H=e.m,M=void 0!==H?H:o.__(0,[1]),N=e.h,W=void 0!==N?N:-1065951377,O=e.w,V=void 0!==O?O:6,j=e.overflow,D=void 0!==j?j:-1065951377,A=e.borderRadius,J=void 0!==A?A:n.px(0),Y=e.onPress,X=e.domProps,q=e.children,Q=i.concat([l.useBoxStyle(h,g,p,b,_,E,w,R,$,G,L,M,W,V,D,J,0),[v,0]]);if(void 0!==Y){var U=Y;u=function(e){return P&&e.currentTarget.blur(),a._1(U,e)}}else u=void 0;return c.createElement(s.make,{tag:r,onPress:u,style:Q,domProps:X,children:q})};t.make=u},,,,,,,,function(e,t,r){"use strict";var n=r(2),i=r(13),o=r(10),a=r(11).create("Lab-Revy.InvalidValue");function c(e,t,r){return i.caml_lessthan(r,e)?e:i.caml_greaterthan(r,t)?t:r}function l(e){return 255*(e<=.00304?12.92*e:1.055*Math.pow(e,1/2.4)-.055)}function s(e){return e>.206896552?e*e*e:.12841855*(e-.137931034)}function u(e){var t=(e[0]+16)/116,r=t+e[1]/500,n=t-e[2]/200;return[.95047*s(r),1*s(t),1.08883*s(n)]}function d(e){var t=e[2],r=e[1],n=e[0];return[l(3.2404542*n-1.5371385*r-.4985314*t)+.5|0,l(-.969266*n+1.8760108*r+.041556*t)+.5|0,l(.0556434*n-.2040259*r+1.0572252*t)+.5|0]}function v(e){var t=e/255;return t<=.04045?t/12.92:Math.pow((t+.055)/1.055,2.4)}function m(e){return e>.008856452?Math.pow(e,1/3):e/.12841855+.137931034}function h(e){var t=v(e[0]),r=v(e[1]),n=v(e[2]);return[m((.4124564*t+.3575761*r+.1804375*n)/.95047),m((.2126729*t+.7151522*r+.072175*n)/1),m((.0193339*t+.119192*r+.9503041*n)/1.08883)]}function f(e){var t=e[1],r=116*t-16;return[r<0?0:r,500*(e[0]-t),200*(t-e[2])]}function g(e,t){return[c(0,100,t[0]+e),t[1],t[2]]}function y(e,t,r){var n=u(t),i=n[2],o=n[1],a=n[0],c=u(r);return f(h(d([a+e*(c[0]-a),o+e*(c[1]-o),i+e*(c[2]-i)])))}t.InvalidValue=a,t.clamp=c,t.toInt=function(e){return e+.5|0},t.Constants=[18,.95047,1,1.08883,.137931034,.206896552,.12841855,.008856452],t.xyz_rgb=l,t.lab_xyz=s,t.labToXyz=u,t.xyzToRgb=d,t.toRGB=function(e){return d(u(e))},t.toCssRGB=function(e){var t=d(u(e));return n.rgb(t[0],t[1],t[2])},t.rgb_xyz=v,t.xyz_lab=m,t.rgbToXyz=h,t.xyzToLab=f,t.fromRGB=function(e){return f(h(e))},t.fromCssRGB=function(e){var t=e[1];return f(h([t[0],t[1],t[2]]))},t.lighten=g,t.highlight=function(e,t){var r=t[0],n=r>50;return g(o.imul(n?-1:1,e),[r,t[1],t[2]])},t.mix=y,t.mixRgb=function(e,t,r){return d(u(y(e,f(h(t)),f(h(r)))))}},function(e,t,r){"use strict";var n=r(2),i=r(1),o=r(0),a=r(6),c=r(17);var l=function(e){var t=e.title,r=e.children;return o.createElement(a.make,{m:i.__(2,[i.__(0,[10])]),children:o.createElement(a.make,{wrap:-822134326,w:5,children:null},o.createElement(c.make,{level:3,children:t}),o.createElement(a.make,{style:[n.maxWidth(n.pct(100)),0],direction:5693978,children:r}))})};t.make=l},function(e,t,r){"use strict";var n=r(2),i=r(0),o=r(6),a=r(9);var c=function(e){var t=e.title,r=e.subtitle;return i.createElement(o.make,{justify:98248149,h:n.vh(80),w:5,children:null},i.createElement(a.$$String[0],{weight:4,tag:"div",size:8,color:11,children:t}),i.createElement(a.$$String[0],{weight:3,tag:"div",size:3,color:12,children:r}))};t.make=c},,,,function(e,t,r){e.exports=r(34)},function(e,t,r){"use strict";var n=r(35),i=r(0);r(69).renderToElementWithId(i.createElement(n.make,{}),"root")},function(e,t,r){"use strict";var n=r(2),i=r(52),o=r(1),a=r(3),c=r(0),l=r(67),s=r(6),u=r(7),d=r(68);var v=function(e){var t=u.Styles[16](0)?1:0,r=c.useState(function(){}),v=r[1],m=r[0],h=function(e){return a._1(v,function(e){return t?void 0===e||e?0:1:void 0!==e&&e?0:1})},f=(void 0!==m?m:t)?d.theme:u.DefaultTheme[0];return u.Styles[17]([n.backgroundColor(f[0][10]),[n.margin(n.px(0)),[n.padding(n.px(0)),0]]]),c.createElement(u.Context[2][0],{value:f,children:c.createElement(c.Fragment,void 0,c.createElement(l.make,{toggleTheme:h}),c.createElement(s.make,{alignContent:98248149,m:o.__(0,[0]),children:c.createElement(i.make,{toggleTheme:h})}))})};t.make=v},,,,,,,,,,,,,,,,,function(e,t,r){"use strict";var n=r(1),i=r(0),o=r(6),a=r(54),c=r(29),l=r(9),s=r(55),u=r(65),d=r(17),v=r(66);var m=function(e){return e.toggleTheme,i.createElement(o.make,{tag:"main",align:-162316795,backgroundColor:5,p:n.__(0,[4]),m:n.__(0,[0]),w:5,children:i.createElement(i.Fragment,void 0,i.createElement(c.make,{title:"Revy",subtitle:"A higher order design system for ReasonReact."}),i.createElement(o.make,{m:n.__(2,[7]),w:5,children:null},i.createElement(d.make,{children:"Revy.Core"}),i.createElement(l.Paragraph[0],{children:"Consistency, colors, typography, motion... A lot of things are hard to manage in a design system. Revy aims to make these things easier."}),i.createElement(l.Paragraph[0],{children:"You create a theme by providing some input to `Revy.Core.make()`. Then you access everything included in the theme \u2013 colors, fonts, space variables etc. \u2013 via a set of variants and functions supplied by Revy. Revy.Core provides functions for color manipulation, layout, spacing, typography and more and makes it easy to build consistent, accessible and beautiful user interfaces."}),i.createElement(l.Paragraph[0],{children:"It's easy to create multiple themes, if you want to provide different branding styles (or a dark mode like this page). You can even use different themes at the same time, which could be useful for sidebars or other pop-in content."}),i.createElement(d.make,{level:2,children:"Example"}),i.createElement(l.Paragraph[0],{children:"This is just a trivial example of how to create a theme and add it to your app. More examples are coming soon..."}),i.createElement(l.Code[0],{children:'let theme = Revy.Core.make();\n\n[@react.component]\nlet make = () => {\n  <Revy.Core.Context.Provider value=theme>\n    <Text.String\n      color=Revy.Core.Colors.QuietText\n      size=2\n    >\n        "My first app"\n    </Text.String>\n  </Revy.Core.Context.Provider>\n};'})),i.createElement(d.make,{children:"Revy.UI"}),i.createElement(o.make,{m:n.__(2,[7]),children:i.createElement(l.Paragraph[0],{children:"Revy makes it easy to build your own components, but it also comes with a set of components of its own. You can use them as a starting point for your design system, an inspiration or a cautionary example."})}),i.createElement(v.make,{}),i.createElement(s.make,{}),i.createElement(a.make,{}),i.createElement(u.make,{}))})};t.make=m},,function(e,t,r){"use strict";var n=r(0),i=r(6),o=r(9),a=r(28);var c=function(e){return n.createElement(a.make,{title:"Typography",children:n.createElement(i.make,{w:5,children:n.createElement(n.Fragment,void 0,n.createElement(i.make,{children:n.createElement(o.$$String[0],{weight:4,size:5,children:"Extra bold and very big"})}),n.createElement(i.make,{children:n.createElement(o.$$String[0],{weight:3,size:4,children:"Bold and big"})}),n.createElement(i.make,{children:n.createElement(o.$$String[0],{weight:1,size:3,children:"Light and tall, like a basketball player"})}),n.createElement(i.make,{children:n.createElement(o.$$String[0],{weight:0,size:2,children:"Supermodel style"})}),n.createElement(i.make,{children:n.createElement(o.$$String[0],{size:1,children:"Perfectly average"})}),n.createElement(i.make,{children:n.createElement(o.$$String[0],{size:0,children:"This is nothing at all"})}),n.createElement(i.make,{children:n.createElement(o.$$String[0],{size:-1,children:"A bit smaller"})}),n.createElement(i.make,{children:n.createElement(o.$$String[0],{size:-2,color:12,children:"So tiny and quiet you almost don't notice it"})}))})})};t.make=c},function(e,t,r){"use strict";var n=r(56),i=r(1),o=r(0),a=r(18);var c=function(e){return o.createElement(a.ComponentsCard[0],{title:"Buttons",children:null},o.createElement(a.Box[1],{align:924268066,direction:5693978,children:null},o.createElement(a.Button[1],{onClick:function(e){return console.log("Secondary",e),0},variant:4,size:2,m:i.__(0,[2]),children:n.s("Click me")}),o.createElement(a.Button[1],{onClick:function(e){return console.log("Primary",e),0},variant:3,m:i.__(0,[2]),children:n.s("Click me")}),o.createElement(a.Button[1],{onClick:function(e){return console.log("Error",e),0},variant:0,m:i.__(0,[2]),children:n.s("Click me")}),o.createElement(a.Button[1],{onClick:function(e){return console.log("Warning",e),0},variant:1,m:i.__(0,[2]),children:n.s("Click me")}),o.createElement(a.Button[1],{onClick:function(e){return console.log("Success",e),0},variant:2,size:0,m:i.__(0,[2]),children:n.s("Click me")})),o.createElement(a.Box[1],{align:662439529,direction:5693978,children:null},o.createElement(a.Button[1],{onClick:function(e){return console.log("Secondary outline",e),0},variant:4,size:2,outline:!0,m:i.__(0,[2]),children:n.s("Click me")}),o.createElement(a.Button[1],{onClick:function(e){return console.log("Primary outline",e),0},variant:3,outline:!0,m:i.__(0,[2]),children:n.s("Click me")}),o.createElement(a.Button[1],{onClick:function(e){return console.log("Error outline",e),0},variant:0,outline:!0,m:i.__(0,[2]),children:n.s("Click me")}),o.createElement(a.Button[1],{onClick:function(e){return console.log("Warning outline",e),0},variant:1,outline:!0,m:i.__(0,[2]),children:n.s("Click me")}),o.createElement(a.Button[1],{onClick:function(e){return console.log("Success outline",e),0},variant:2,size:0,outline:!0,m:i.__(0,[2]),children:n.s("Click me")})))};t.make=c},function(e,t,r){"use strict";var n=r(57).toArray;t.s=function(e){return e},t.i=function(e){return String(e)},t.a=function(e){return e},t.l=n},,,,,function(e,t,r){"use strict";var n=r(2),i=r(5),o=r(1),a=r(0),c=r(7),l=r(16);function s(e,t,r){var a=c.Styles[13](0);return i.concat([[n.backgroundColor(c.Styles[7](void 0,void 0,o.__(0,[15,5]))),[n.flexWrap(-822134326),[n.borderRadius(n.px(6)),[n.borderWidth(n.px(1)),[n.borderColor(c.Styles[7](void 0,void 0,o.__(0,[25,5]))),[n.borderStyle(12956715),[n.boxShadow(void 0,n.px(4),n.px(10),void 0,void 0,n.hsla(0,0,0,a?.15:.45)),0]]]]]]],[c.Styles[5](e),[c.Styles[4](t),0]]])}var u=function(e){var t=e.tag,r=void 0!==t?t:"div";e.a11yTitle;var n=e.style,c=void 0!==n?n:0;e.color,e.grow;var u=e.p,d=void 0!==u?u:o.__(0,[3]),v=e.m,m=void 0!==v?v:o.__(0,[1]),h=e.domProps,f=e.children,g=i.concat([s(d,m),[c,0]]);return a.createElement(l.make,{tag:r,style:g,domProps:h,children:f})};t.useCardStyle=s,t.make=u},function(e,t,r){"use strict";var n=r(2),i=r(5),o=r(1),a=r(0),c=r(7),l=r(9),s=r(19);function u(e,t){return[n.display(423610969),[n.textDecoration(131142924),[n.cursor(-786317123),[n.borderStyle(-922086728),[n.color(c.Styles[7](void 0,void 0,e)),[n.transition(200,void 0,void 0,"color"),[n.hover([n.color(c.Styles[7](-40,void 0,e)),0]),[n.focus([n.outlineStyle(-922086728),[n.boxShadow(void 0,n.px(0),n.px(0),n.px(1),!0,c.Styles[7](void 0,void 0,0)),0]]),[n.active([n.outlineStyle(-922086728),[n.boxShadow(void 0,n.px(0),n.px(0),n.px(1),!0,c.Styles[7](void 0,void 0,13)),0]]),0]]]]]]]]]}var d=[function(e){var t=e.onClick,r=void 0!==t?t:function(e){return 0},n=e.color,d=void 0!==n?n:0,v=e.size,m=void 0!==v?v:0,h=e.lineHeight,f=void 0!==h?h:0,g=e.m,y=void 0!==g?g:o.__(0,[0]),p=e.weight,k=void 0!==p?p:2,b=e.children,S=l.useTextStyles(m,d,void 0,f,k,0),_=u(d);return a.createElement(s.make,{tag:"button",style:i.concat([S,[_,[c.Styles[4](y),0]]]),grow:0,onPress:r,children:b})}],v=function(e){var t=e.href,r=e.onClick,s=void 0!==r?r:function(e){return 0},d=e.color,v=void 0!==d?d:0,m=e.size,h=void 0!==m?m:0,f=e.lineHeight,g=void 0!==f?f:0,y=e.m,p=void 0!==y?y:o.__(0,[0]),k=e.weight,b=void 0!==k?k:2,S=e.children,_=l.useTextStyles(h,v,void 0,g,b,0),x=u(v);return a.createElement("a",{className:n.style(i.concat([_,[x,[c.Styles[4](p),0]]])),href:t,onClick:s},S)};t.useLinkStyle=u,t.make=v,t.Button=d},function(e,t,r){"use strict";var n=r(2),i=r(5),o=r(1),a=r(3),c=r(0),l=r(7),s=r(19);function u(e,t,r,o,c,s){var u;switch(o){case 0:u=[l.Styles[10](-1),2,3];break;case 1:u=[l.Styles[10](0),3,4];break;case 2:u=[l.Styles[10](1),4,5]}var d=u[0],v=[n.padding2(l.Styles[8](void 0,u[1]),l.Styles[8](void 0,u[2])),[n.textDecoration(-922086728),[n.textAlign(98248149),[n.alignContent(98248149),[n.flexGrow(0),[n.cursor(-786317123),[n.transition(200,void 0,void 0,"all"),[n.fontSize(d),[n.lineHeight(l.Styles[12](d,void 0,0)),[n.fontWeight(-1055161979),0]]]]]]]]]];return i.concat([l.Styles[4](r),[v,[function(e){var r;if(t)switch(e){case 0:r=[4,13];break;case 1:r=[3,13];break;case 2:r=[2,13];break;case 3:r=[0,13];break;case 4:r=[1,13]}else switch(e){case 0:r=[9,4];break;case 1:r=[8,3];break;case 2:r=[10,2];break;case 3:r=[6,0];break;case 4:r=[7,1]}var i=r[1],o=r[0],c=[t?n.boxShadow(void 0,n.px(0),n.px(0),n.px(2),!0,l.Styles[7](50,void 0,o)):n.boxShadow(void 0,n.px(0),n.px(0),n.px(1),!0,l.Styles[7](15,void 0,i)),[n.borderWidth(n.px(0)),[n.borderStyle(12956715),0]]],s=l.Styles[13](0)?function(e){return n.rgba(0,0,0,e)}:function(e){return n.rgba(255,255,255,e)};return[n.fontFamily(l.Styles[9](0)),[n.color(l.Styles[7](t?50:0,void 0,o)),[n.borderRadius(n.px(6)),[n.textTransform(-415330030),[n.backgroundColor(l.Styles[7](void 0,void 0,i)),[n.hover([n.backgroundColor(t?a._1(s,.05):l.Styles[7](-20,void 0,i)),0]),[n.disabled([n.opacity(.7),[n.hover([n.backgroundColor(l.Styles[7](void 0,void 0,i)),0]),0]]),[n.focus([n.outlineStyle(-922086728),[n.backgroundColor(t?a._1(s,.1):l.Styles[7](30,void 0,i)),0]]),[n.active([n.backgroundColor(l.Styles[7](20,void 0,i)),0]),c]]]]]]]]]}(e),0]]])}var d=[function(e){var t=e.onClick,r=e.variant,i=void 0!==r?r:3,l=e.href,s=(e.disabled,e.outline),d=void 0!==s&&s,v=e.size,m=void 0!==v?v:1,h=e.m,f=void 0!==h?h:o.__(0,[1]),g=e.onlyFocusOnTab,y=void 0===g||g,p=e.children;return c.createElement("a",{className:n.style(u(i,d,f,m)),href:l,onClick:function(e){return y&&e.currentTarget.blur(),a._1(t,e)}},p)}],v=function(e){var t=e.onClick,r=e.variant,n=void 0!==r?r:4,i=e.size,a=void 0!==i?i:1,l=e.disabled,d=void 0!==l&&l,v=e.outline,m=void 0!==v&&v,h=e.onlyFocusOnTab,f=void 0===h||h,g=e.m,y=void 0!==g?g:o.__(0,[1]),p=e.children;return c.createElement(s.make,{tag:"button",style:u(n,m,y,a),onlyFocusOnTab:f,onPress:t,domProps:{disabled:d},children:p})};t.useButtonStyles=u,t.make=v,t.Link=d},function(e,t,r){"use strict";var n=r(2),i=r(5),o=r(1),a=r(0),c=r(7),l=r(9);function s(e,t){var r=c.Styles[13](0),o=c.Styles[13](0);return i.concat([[n.padding2(c.Styles[8](0,3),c.Styles[8](0,3)),[n.textDecoration(-922086728),[n.cursor(-786317123),[n.lineHeight(c.Styles[12](c.Styles[10](0),void 0,0)),[n.fontSize(c.Styles[10](0)),[n.fontFamily(c.Styles[9](0)),[n.borderWidth(n.px(0)),[n.borderColor(c.Styles[7](void 0,void 0,13)),[n.borderRadius(n.px(6)),[n.borderStyle(12956715),[n.backgroundColor(r?n.rgba(0,0,0,.05):n.rgba(255,255,255,.05)),[n.color(c.Styles[7](void 0,void 0,11)),[n.boxShadow(void 0,n.px(0),n.px(0),n.px(1),!0,o?n.rgba(0,0,0,.07):n.rgba(255,255,255,.07)),[n.focus([n.outlineStyle(-922086728),[n.boxShadow(void 0,n.px(0),n.px(0),n.px(1),!0,c.Styles[7](void 0,void 0,0)),0]]),[n.disabled([n.opacity(.7),0]),0]]]]]]]]]]]]]]],[c.Styles[4](e),0]])}var u=[function(e){e.onClick;var t=e.onChange,r=e.label,c=e.id,l=void 0!==c?c:"",u=e.type_,d=void 0!==u?u:"text",v=e.disabled,m=void 0!==v&&v,h=e.styles,f=e.onFocus,g=void 0!==f?f:function(e){return 0},y=e.onBlur,p=void 0!==y?y:function(e){return 0},k=e.placeholder,b=void 0!==k?k:"",S=e.m,_=void 0!==S?S:o.__(0,[1]),x=e.value;return a.createElement("input",{className:n.style(void 0!==h?i.concat([s(_),[h,0]]):s(_)),id:l,disabled:m,label:r,placeholder:b,type:d,value:x,onFocus:g,onBlur:p,onChange:t})}];var d=[function(e){var t=e.children,r=e.htmlFor;return a.createElement("label",{className:n.style(l.useTextStyles(-1,12,void 0,1,2,0)),htmlFor:r},t)}];t.useInputStyles=s,t.Input=u,t.Label=d},function(e,t,r){"use strict";var n=r(2),i=r(1),o=r(0),a=r(6),c=r(9),l=r(17);var s=function(e){return e.toggleTheme,o.createElement(a.make,{m:i.__(2,[i.__(0,[10])]),children:o.createElement(a.make,{wrap:-822134326,w:5,children:null},o.createElement(l.make,{level:3,children:"Layout"}),o.createElement(a.make,{style:[n.maxWidth(n.pct(100)),[n.width(n.pct(100)),0]],direction:5693978,children:o.createElement(a.make,{direction:5693978,w:5,children:o.createElement(o.Fragment,void 0,o.createElement(a.make,{backgroundColor:0,p:i.__(0,[3]),h:n.em(10),w:5,children:o.createElement(c.$$String[0],{weight:3,color:6,children:"Full"})}),o.createElement(a.make,{backgroundColor:2,p:i.__(0,[3]),h:n.em(10),w:4,children:o.createElement(c.$$String[0],{weight:3,color:10,children:"Half"})}),o.createElement(a.make,{backgroundColor:3,p:i.__(0,[3]),h:n.em(10),w:i.__(2,[5,5,4]),children:o.createElement(c.$$String[0],{weight:3,color:8,children:"Responsive(Full, Full, Half)"})}),o.createElement(a.make,{backgroundColor:4,p:i.__(0,[3]),h:n.em(10),w:3,children:o.createElement(c.$$String[0],{weight:3,color:9,children:"Third"})}),o.createElement(a.make,{backgroundColor:0,p:i.__(0,[3]),h:n.em(10),w:3,children:o.createElement(c.$$String[0],{weight:3,color:6,children:"Third"})}),o.createElement(a.make,{backgroundColor:2,p:i.__(0,[3]),h:n.em(10),w:3,children:o.createElement(c.$$String[0],{weight:3,color:10,children:"Third"})}))})}))})};t.make=s},function(e,t,r){"use strict";var n=r(1),i=r(3),o=r(0),a=r(18);var c=function(e){var t=o.useState(function(){return""}),r=t[1],c=t[0],l=o.useCallback(function(e){var t=e.currentTarget.value;return i._1(r,function(e){return t})});return o.createElement(a.ComponentsCard[0],{title:"Inputs",children:null},o.createElement(a.Box[1],{direction:-963948842,m:n.__(6,[1,1,3,3]),children:null},o.createElement(a.TextInput[2][0],{children:"Enabled",htmlFor:"foo"}),o.createElement(a.TextInput[1][0],{onChange:l,label:"String",id:"foo",placeholder:"Type something nice",value:c})),o.createElement(a.Box[1],{direction:-963948842,m:n.__(6,[1,1,3,3]),children:null},o.createElement(a.TextInput[2][0],{children:"Disabled",htmlFor:"bar"}),o.createElement(a.TextInput[1][0],{onChange:l,label:"Bar",id:"bar",type_:"number",disabled:!0,placeholder:"Number",value:String(c.length)})))};t.make=c},function(e,t,r){"use strict";var n=r(2),i=r(1),o=r(3),a=r(0),c=r(18),l=r(7);var s=function(e){var t=e.toggleTheme,r=void 0!==t?t:function(e){return 0};return a.createElement(c.View[1],{children:a.createElement(a.Fragment,void 0,a.createElement(c.Box[1],{h:l.Styles[8](void 0,i.__(0,[11]))}),a.createElement(c.Box[1],{style:[n.position(10615156),[n.top(n.px(0)),[n.left(n.px(0)),[n.boxShadow(void 0,n.px(0),void 0,n.px(1),void 0,n.rgba(0,0,0,.2)),[n.unsafe("willChange","transition"),[n.zIndex(1),0]]]]]],align:98248149,alignContent:98248149,backgroundColor:i.__(0,[20,5]),direction:5693978,p:i.__(0,[3]),w:i.__(1,[n.vw(100)]),children:a.createElement(a.Fragment,void 0,a.createElement(c.Box[1],{grow:1,direction:5693978,children:a.createElement(c.$$Text[3][0],{weight:3,size:1,children:"Revy"})}),a.createElement(c.Box[1],{grow:0,direction:5693978,children:null},a.createElement(c.Link[1],{href:"https://github.com/eldh/revy",color:1,m:i.__(0,[2]),children:"Github"}),a.createElement(c.Link[2][0],{onClick:function(e){return o._1(r,0)},color:1,m:i.__(0,[2]),children:"Toggle dark theme"})))}))})};t.make=s},function(e,t,r){"use strict";var n=r(2),i=r(27),o=r(7),a=[["-apple-system",["BlinkMacSystemFont",["sans-serif",0]]],["-apple-system",["BlinkMacSystemFont",["sans-serif",0]]],["monospace",0],["-apple-system",["BlinkMacSystemFont",["sans-serif",0]]]],c=[i.toCssRGB(i.fromRGB([110,181,247])),i.toCssRGB(i.highlight(70,i.fromRGB([110,181,247]))),i.toCssRGB(i.fromRGB([227,230,232])),i.toCssRGB(i.highlight(90,i.fromRGB([227,230,232]))),n.rgb(88,214,21),i.toCssRGB(i.lighten(-90,i.fromRGB([88,214,21]))),i.toCssRGB(i.fromRGB([235,180,71])),i.toCssRGB(i.lighten(-90,i.fromRGB([235,180,71]))),n.rgb(240,72,72),n.rgb(0,0,0),n.rgb(20,20,20),n.rgb(255,255,255),n.rgb(180,180,180)],l=o.make(1.2,16,4,a,c,700,0);t.fonts=a,t.colors=c,t.theme=l}],[[33,1,2]]]);
//# sourceMappingURL=main.f95a2a60.chunk.js.map