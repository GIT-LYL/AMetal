/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief WWDT ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. �� WWDT ʹоƬ��λ��������ʾ "The chip Reset by WWDT\r\n"��
 *   2. �޸ĺ궨�� __WWDT_FEED_TIME_MS ��ֵ������ 1500ms(���� 5ms ���)��оƬ��λ��
 *   3. �޸ĺ궨�� __WWDT_FEED_TIME_MS ��ֵ��С�� 1500ms(���� 5ms ���)�������������С�
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_14 �������� PC ���ڵ� TXD��
 *       PIO0_23 �������� PC ���ڵ� RXD��
 *    3. WDT ʱ�ӣ�0.6MHz��64 ��Ƶ��ʱ��Ƶ�� 9.375KHz��WDT �������̶� 4 ��Ƶʱ�ӣ�
 *    4. Ƭ�� WDTOSC Ƶ�ʲ���������� 40% ����
 *
 * \par Դ����
 * \snippet demo_am845_core_std_wwdt.c src_am845_core_std_wwdt_wdt
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-09  sss, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_std_wwdt
 * \copydoc demo_am845_core_std_wwdt.c
 */

/** [src_am845_core_std_wwdt_wdt] */
#include "ametal.h"
#include "am_wdt.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_lpc84x_inst_init.h"
#include "hw/amhw_lpc84x_clk.h"
#include "hw/amhw_lpc84x_syscon.h"
#include "demo_std_entries.h"

/**
 * \brief ���Ź���ʱʱ��
 *
 * \note ��Ϊ���Ź��ڲ�ʱ�� WDTOSC ���������� __WWDT_TIMEOUT_MS ��Ӧ��ʵ��ʱ��
 *       �������
 */
#define __WWDT_TIMEOUT_MS       1500

/**
 * \brief ���Ź�ι��ʱ�䣬��ι��ʱ�䳬�� __WWDT_TIMEOUT_MS ��ֵ������ 5ms ���ϣ�,
 *        ��������Ź��¼�
 */
#define __WWDT_FEED_TIME_MS     1600

/**
 * \brief �������
 */
void demo_am845_core_std_wwdt_entry (void)
{
    am_kprintf("demo am845_core std wwdt!\r\n");

    if ((amhw_lpc84x_syscon_rst_stat_get() & AMHW_LPC84X_SYSCON_RSTSTAT_WDT) != 0) {

        amhw_lpc84x_syscon_rst_stat_clr(AMHW_LPC84X_SYSCON_RSTSTAT_WDT);

        AM_DBG_INFO("The chip Reset by WWDT\r\n");
    } else {
        AM_DBG_INFO("The chip Reset by External Reset Pin \r\n");
    }

    AM_DBG_INFO("The wdt osc freq is %d\r\n", amhw_lpc84x_clk_wdt_rate_get());

    demo_std_wdt_entry(am_lpc84x_wwdt_inst_init(),
                       __WWDT_TIMEOUT_MS,
                       __WWDT_FEED_TIME_MS);
}
/** [src_am845_core_std_wwdt_wdt] */

/* end of file */