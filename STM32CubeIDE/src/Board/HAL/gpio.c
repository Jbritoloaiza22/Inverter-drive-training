
/* gpio mode register values */
#define GPIO_MODE_INPUT			0x00 // use port as input
#define GPIO_MODE_OUTPUT_PP		0x01 // use port as output (push-pull)
#define GPIO_MODE_OUTPUT_OD		0x02 // use port as output (open-drain)
#define GPIO_MODE_AF_PP			0x03 // use port as alternate function (push-pull)
#define GPIO_MODE_AF_OD			0x04 // use port as alternate function (open-drain)
#define GPIO_MODE_ANALOG		0x05 // use port as analog

/*gpio output type register values */
#define GPIO_OTYPE_PP			0x00 // push-pull output
#define GPIO_OTYPE_OD			0x01 // open-drain output

/*gpio output speed register values */
#define GPIO_SPEED_LOW			0x00 // low speed
#define GPIO_SPEED_MEDIUM		0x01 // medium speed
#define GPIO_SPEED_HIGH			0x02 // high speed
#define GPIO_SPEED_VERY_HIGH	0x03 // very high speed

/*gpio pull-up/pull-down register values */
#define GPIO_NOPULL				0x00 // no pull-up, pull-down
#define GPIO_PULLUP				0x01 // pull-up
#define GPIO_PULLDOWN			0x02 // pull-down

/*gpio pin state values */
#define GPIO_PIN_RESET			0x00 // pin reset
#define GPIO_PIN_SET				0x01 // pin set

/* alternative function defines*/
#define GPIO_AF0					0x00
#define GPIO_AF1					0x01
#define GPIO_AF2					0x02
#define GPIO_AF3					0x03
#define GPIO_AF4					0x04
#define GPIO_AF5					0x05
#define GPIO_AF6					0x06
#define GPIO_AF7					0x07
#define GPIO_AF8					0x08
#define GPIO_AF9					0x09
#define GPIO_AF10					0x0A
#define GPIO_AF11					0x0B
#define GPIO_AF12					0x0C
#define GPIO_AF13					0x0D
#define GPIO_AF14					0x0E
#define GPIO_AF15					0x0F




